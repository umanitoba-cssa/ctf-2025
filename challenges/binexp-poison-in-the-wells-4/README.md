# poison-in-the-wells-4
- Revision 0
- Binary Exploitation
- Hard
- 450 Points

## Description
You're good kid! So we've got a name to work with now, but we don't actually have any *proof* that Mr. Cain is connected to this case yet.

So how do we link Mr. Cain to the crime? Well, I heard from the cops that he *was* a suspect in the case, but Mr. Cain had an alibi - his Google maps timeline showed he was at a pub on the other end of the city at the time of the murder. Look kid, I've worked in this industry long enough to know that GPS data ain't worth nothin' if you don't know who actually had posession of the tracking device. And Mr. Cain claims he was drinking alone, so there's no one else who can confirm he was really at that location. Not a very strong alibi if you ask me!

Let's review what we know: First, the cause of Mr. Wells' death is unknown, but we do know that someone with a high level permission on the file server was tampering with the case documents. Second, a Cybertruck was spotted near the scene of the crime, and we know Mr. Cain owns one. Third, Mr. Cain claims he was out for drinks, but he has no one who can confirm it.

All this is pointing to one thing: money. What if we could knock out three birds with one stone: figure out who he might work for that could give him access to the document server, figure out if he really bought that Cybertruck for himself, and figure out if he really was out buying drinks at the pub? 

I say we take a look at his bank account. I happen to have an account at the very same branch of Mr. Cain! Not sure if this will be of any help, but feel free to poke around my account. My username is `dgumshoe` and my password is `w1z@rdk1d`.

This could be it kid! You've done well so far, if you can also find a way to break into the transaction database of a literal bank, we might crack this case!

Connect with SSH:
- Enter this command in your terminal: `ssh gateway@poison-in-the-wells-4.ctf.umanitobacssa.ca -p 30204`
- Enter this password when prompted: `ctf2025!`

## Hints
1. You'll need to use everything you've learned so far. No help for this one!

## Solution
This is a multistep process. There are four exploits you need to use:

1. The login function uses gets to read the password. This allows you to overwrite the username in the userdata struct to anything you want, but since the password is already loaded the program will check the password of the original username you enter. This means you can login as anyone, even users that don't exist.
2. The login function only checks the first N characters of the password input string, where N is the number of characters in the real password. This means we can enter pretty much any string we want into the password input and pass the check as long as what we enter starts with the correct password.
3. The auth gate function has a printf vulnerability allowing us to read the stack data. **ASLR and PIE is enabled for this binary** unlike the previous ones, but we can **bypass ASLR and PIE** by leaking the function pointer of the transactions function using this printf vulernability.
4. The same gets vulnerability in the process_input function remains, so once we leak the address for transactions we can overwrite our return address to jump there.

One other quirk is that all usernames get rear-padded with zeroes to exactly 15 characters. This makes utilizing the buffer overflow vulnerability a bit easier than it otherwise would be.

So the steps are:
1. Start a login for dgumshoe with `login dgumshoe`
2. Enter a string that begins with the password, but is also long enough to overflow the buffer and overwrite the username on the userData struct. To take advantage of the printf vulnerability in the auth_gate function, we will put a format string token to print the 7th pointer (which will be the pointer we want). Eg. `w1z@rdk1dAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAhcain0000P%7$pP`
3. After submitting the above we will login as `hcain0000P%7$pP` which is not a real user, but that's ok.
4. Run the `transactions` command. Our username will get printed back to us but the format string token will be replaced with the address of the transactions function. The password prompt will also fail because the function detects our user doesn't exist.
5. Logout with the `logout` command
6. Start a login for dgumshoe again with `login dgumshoe`
7. This time we want to login as hcain properly. To do this we will overflow the buffer again but simply include hcain with the correct number of padded zeroes afterwards. Eg. `w1z@rdk1dAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAhcain0000000000`
8. If we try to call transactions at this point, we will be prompted to enter the password again, but we don't actually know it. Instead, use the buffer overflow vulnerability in the process_input function to overwrite the return address to jump us to the transactions function. So, 64 + 8 padding characters, then the address of the function.
9. The flag has been printed

**If it doens't work, try again**. It's possible to get unlucky with the ASLR'd address such that it's not possible to send it over an SSH connection - for example, \x00, \x13, \x08, \x0A and others can cause problems. But the good news is that since it's ASLR, you can just keep rerunning it until you get an address that works.

A pwntools solution script is provided in ./solution

## Flag
`cssactf{@sLR-bYP@5s-5O1v3s-t#E-c4S3-dff269be}`