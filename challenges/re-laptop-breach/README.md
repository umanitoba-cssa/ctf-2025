# laptop-breach 
- Reverse Engineering
- Medium

## Description
We found what we strongly believe is the killer's laptop. There's a slight issue though, we can't seem to get in. Can you give it a crack?

## Hint
1. What does `0x30` mean? Why might we be adding `-0x30`?

## Solution
By carefully making our way through the execution flow with a decompiler (e.g. IDA Pro, Ghidra, Binary Ninja, etc.), we can slowly start to
determine the password criteria. A valid password is one defined as:
- Being between 6 and 15 characters
- Having digits summing up to 15
- Containing the substring "win"
- Containing at least one non-alphanumeric character
- And having the first digit in the password be 6

Note: The challenge is technically solveable without determining the last criterion. Once players have figured out the first four criteria,
the last one can be "brute forced". In the decompilation for the last function, we see that we add `-0x30` again.  Since we have already
determined this to mean converting from decimal to ascii, we can modify the numbers in our string (while still satisfying the second criterion)
until we get the success flag.

Alternatively, one can simply locate the array of function pointers in the decompiled program and reverse each one of them. This requires brute
force and trying each flag until one works, but in some instances this may be an easier solution than simply following the program flow and
deriving a correct password.

## Flag
`cssactf{4cce55_gr4nt3d!}`