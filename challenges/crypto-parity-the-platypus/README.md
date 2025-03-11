# Parity the Platypus
- Revision 0
- Cryptography

## Description
Dear Detective,

I finished creating a program that should help remove some tedious work in detective work and the program has been encrypted and sent as binary. Unfortunately, I learned that an evil-doer has blasted it with their least-significant-bit-flip-inator and the program won't decrypt anymore.

Luckily, I have a failsafe mechinism implemented where the 8th bit from the left (1st bit from the right) must be 1 if the number of 1s is odd and 0 if the number of 1s is even. Perhaps if we figure out which 8-bit words were affected (and no longer pass the failsafe), we can actually gain information about this evil-doer! I have split up the program into lines of 8-bits for ease of digestion.

I await your reply,
P.P.

## Solution
Calculate the parity and see which lines don't match and were thus affected. Alternatively, calculate the opposite, or, even odd 1s parity and see which lines *do* match. Convert those binary numbers to ASCII characters to obtain the flag.

## Flag 
`cssactf{Bit_By_Bit_I_Weep}`
