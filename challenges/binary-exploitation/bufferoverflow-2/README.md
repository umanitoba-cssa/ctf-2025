# bufferoverflow-2
- Revision 0
- Binary Exploitation
- Medium
- 300 Points

## Description
That witness testimony about the truck was a good find! Well, maybe. More like it's the only thing resembling a lead that we have, so might as well follow it.

There's only one Tesla dealership in town, so we asked to take a look at their transaction database. They agreed to let us see a list of purchases, but it just has dates and subtotals. They won't let us see any of the transaction details without a warrant.

Well, getting a warrant is far too much paperwork for my tastes. Maybe you can find a hole in the system to get us the full transaction details?

## Hints
1. The authorization level gets checked in the process_input function after typing the details command. Is there some other way to call the details function?
2. The process_input function returns back to the main function after each command before getting called again. Is there something we can do to "return" somewhere else?
3. The process_input remembers where to return by storing a memory address on the stack, and the get_details function needs the month and year to be passed in as parameters on the stack. Do we have some way to control data on the stack?
4. This might be a helpful resource: <https://ctf101.org/binary-exploitation/buffer-overflow/>

## Solution
Overflow the password input buffer with the correct number of characters to overwrite the correct password buffer such that the contents of both buffers match. 96 of the same letters will work.

## Flag
`cssactf{lE7-m3-Se3-t4e-Wi7n3ss-Te5t1m0ny-82fe2946}`