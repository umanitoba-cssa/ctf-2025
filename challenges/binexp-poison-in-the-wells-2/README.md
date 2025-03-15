# poison-in-the-wells-2
- Revision 0
- Binary Exploitation
- Medium
- 300 Points

## Description
That witness testimony about the truck was a good find! Well, maybe. More like it's the only thing resembling a lead that we have, so might as well follow it.

There's only one Tesla dealership in town, so we asked to take a look at their transaction database. They agreed to let us see a list of purchases, but it just has dates and subtotals. They won't let us see any of the transaction details without a warrant.

Well, getting a warrant is far too much paperwork for my old age. Maybe you can find a hole in the system to get us the full transaction details?

Connect with SSH:
- Enter this command in your terminal: `ssh guest@poison-in-the-wells-2.ctf.umanitobacssa.ca -p 30202`
- Enter this password when prompted: `ctf2025!`

*A copy of the server software and source code is provided for your reference. The binary is identical to the hosted version, however the flag can only be found in the hosted version of the program.*

## Hints
1. The authorization level gets checked in the process_input function after typing the details command. Is there some other way to call the details function?
2. The process_input function returns back to the main function after each command before getting called again. Is there something we can do to "return" somewhere else?
3. The process_input function remembers where to return by storing a memory address on the stack. Do we have some way to control data on the stack?
4. This might be a helpful resource: <https://ctf101.org/binary-exploitation/buffer-overflow/>

## Solution
We can utilize the same buffer overflow exploit in the process_input function, but this time to overwrite the return address on the stack which normally jumps back to the main function. Using the `checksec` command on the provided binary we can see that ASLR is disabled, so we can use pwntools or a decompiler like Ghidra to figure out the virtual address of the `get_details` function. Without ASLR and PIE, this address will stay the same every time the binary is run.

There's one small catch, the `get_details` function needs the file path to already be loaded into the global variable. The function is coded poorly such that this file path gets loaded before the authorization level gets checked, so we can just enter `details 02 2025` once which fails, then we can send our payload to overwrite the stack return address with the address of the `get_details` function to force it to be executed.

A pwntools solution script is provided in ./solution

## Flag
`cssactf{r3TurN-t0-Cu5t0m3R-5ed363eb}`