# Who Added Bits Of Info

## Description

I finished creating a program that should help remove some tedious work in detective work and the program has been converted into binary bits. Unfortunately I learned that a malicious third party added additional bits into the program and it won't run anymore

Luckily I have a failsafe mechinism implemented. Every 8 bits is considered as a chunk. The first 7 bits carry real info whereas the 8 is a parity bit. the 8th bit will be 0 if the number of 1 in thr first 7 is even and 1 otherwise.

If there's a departure from that, the program doesn't run (Think of this as a way to detect if a cosmic ray flipped a bit by accident). This won't help with intentional tampering (such as this problem) but it's effective in detecting if there was unintended changes as any small change will be reflected in the parity bit. 

The textfile has been split into lines of 8 bits in order to make this easier to decode. **Please** do not try to do this manually, use a program

## Solution

The way to find the 8 bits which were unintentionally added is to see if the bits **Don't** match the parity bit. Essentially the opposite condition (if there are 5 ones, the parity bit would be 0). 

## Flag 

`cssactf{Bit_By_Bit_I_Weep}`
