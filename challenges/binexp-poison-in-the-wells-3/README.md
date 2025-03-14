# poison-in-the-wells-3
- Revision 0
- Binary Exploitation
- Medium
- 350 Points

## Description
Hm, a corporate entity buying a CyberTruck? Why? And no lease term? That's quite suspicious indeed!

I went to the agency that handled the insurance registration for the car. Well, they were less than helpful to be honest. I squeezed out of them that Isaac was the employee that handled the sign-up but they wouldn't give us access to any records. So... I "social engineered" this Isaac to get his employee login to the broker's database! That's what the kids call it, right?

I can see that Luxewood is listed under Isaac's account, so that info was right at least. But we need to figure out who is tied to that business registration, and all the contact information for the business registrations are locked behind a password. Can you see if there's some way we can get access to that document?

Connect with SSH:
- Enter this command in your terminal: `ssh isaac@poison-in-the-wells-3.ctf.umanitobacssa.ca -p 30203`
- Enter this password when prompted: `ctf2025!`

*A copy of the server software and source code is provided for your reference. The binary is identical to the hosted version, however the flag can only be found in the hosted version of the program.*

## Hints
1. Is the password for the business contact information being stored somewhere vulnerable?
2. We know how to use a buffer overflow to write data to the stack, but what can we do to read data from the stack?
3. This might be a helpful resource: <https://ctf101.org/binary-exploitation/what-is-a-format-string-vulnerability/>

## Solution
When we enter an unknown command, the program prints our input back to us by directly passing our input string to printf. This means we are able to control the behavior of printf - a format string vulnerability. We can use printf format identifiers to leak as much data off the stack as we want. We have to go pretty deep into the stack, then reassemble the password, but it's in there! Once we get the password we can access the private document for Luxewood.

A pwntools solution script is provided in ./solution

## Flag
`cssactf{S7r1nG-f0Rm@T-c0Ve7A9e-e%c33dEd-d0d40d24}`