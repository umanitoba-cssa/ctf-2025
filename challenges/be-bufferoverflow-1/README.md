# bufferoverflow-1
- Revision 0
- Binary Exploitation
- Easy
- 150 Points

## Description
The coroner on this case gave us access to the relevant case documents on their file server. They told us that one of the witness statements has a password applied to it, but the PD says they never set one. And apparently, they don't have a backup. Sounds fishy if you ask me. Think you could find a way to get access to that document? 

This server software is ancient and the company that wrote it went out of business decades ago over lawsuits related to security flaws in their software... which of course means the PD hasn't bothered to upgrade to anything better. Perhaps you can find one of those flaws? I found a demo copy of the client software and it's source code on the Internet Archive, so take a look.

Connect with SSH:
- Enter this command in your terminal: `ssh detective@bufferoverflow-1.ctf.umanitobacssa.ca -p 30201`
- Enter this password when prompted: `CSSActf2025!`

## Hints
1. The file is protected by a password, maybe there's some way to pass that check without knowing the real password?
2. This might be a helpful resource: <https://ctf101.org/binary-exploitation/buffer-overflow/>

## Solution
Overflow the password input buffer with the correct number of characters to overwrite the correct password buffer such that the contents of both buffers match. 96 of the same letters will work.

## Flag
`CSSACTF{lE7-m3-Se3-t4e-Wi7n3ss-Te5t1m0ny-82fe2946}`