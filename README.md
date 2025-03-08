# Who Added Bits Of Info

## Description

I finished creating a program and already converted into Binary bits. Unfortunately I got a tip that my program has been tampered and additional bits have been added in my program. 

Luckily I have a failsafe mechinism implemented. It is grouped into 9 bits. The first 8 bits carry real info whereas the last bit acts as a parity check (0 if the number of 1s in the previous 8 is even and 1 otherwise)

If there's a departure from that, the program doesn't run (Think of this as a way to detect if a cosmic ray flipped a bit by accident). This won't help with intentional tampering (like this problem) but it's effective in detecting if there was unintended changes. 

The textfile has been split into lines of 9 bits in order to make this easier to decode. **Please** do not try to do this manually, use a program

## Solution

For each line in the file, count the number of 1s in the file. If the parity bit matches with what is expected. Than you are safe to move on. Otherwise copy 8 message bits. These 8 bits are ascii characters and if you convert into a string, you will get the flag.

Update the grammar in this

## Flag 

`cssactf{Bit_By_Bit_I_Weep}`
