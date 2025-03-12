# poison-in-the-wells-1
- Revision 1
- Binary Exploitation
- Easy
- 150 Points

## Description
Hey kid! I think I may be in need of a hacker! The family of the deceased Jonathan Wells say they've gotten a hunch that the cops on this case might not be giving it their all, so they asked me to conduct a private investigation on the side while the police do their work. Not sure what tipped them off, could be all in their heads, who knows! But money is money.

The only problem, well, it's the digital age! And grandpa here doesn't know jack about computers. And it looks like there's some funny business going on with some computers. So I'm calling on you to help me out! Here's the sich.

The coroner on this case gave us access to the relevant documents on their file server. They told me that one of the witness statements has a password applied to it, but the PD says they never set one. And apparently, they don't have a backup. Sounds fishy if you ask me. Think you could find a way to get access to that document? 

This server software is ancient and the company that wrote it filed for bankruptcy decades ago over lawsuits related to security flaws in their software before they got bought out by some megacorp... which of course means the PD hasn't bothered to upgrade to anything better. Perhaps you can find one of those flaws? I found a demo copy of the client software and it's source code on the Internet Archive, so take a look.

Connect with SSH:
- Enter this command in your terminal: `ssh detective@poison-in-the-wells-1.ctf.umanitobacssa.ca -p 30201`
- Enter this password when prompted: `ctf2025!`

*A copy of the server software and source code is provided. The binary 

## Hints
1. The file is protected by a password, maybe there's some way to pass that check without knowing the real password?
2. This might be a helpful resource: <https://ctf101.org/binary-exploitation/buffer-overflow/>

## Solution
Overflow the password input buffer with the correct number of characters to overwrite the correct password buffer such that the contents of both buffers match. 96 of the same letters will work.

`AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`

A pwntools solution script is provided in ./solution

## Flag
`cssactf{lE7-m3-Se3-t4e-Wi7n3ss-Te5t1m0ny-82fe2946}`