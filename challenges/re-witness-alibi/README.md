# witness-alibi
- Reverse Engineering
- Easy

## Description
We got access to the alibi of one of our witnesses. We've taken a look and checked everything, but it doesn't seem to hold up. She swears she's innocent but we can't seem to find anything here to support that claim.
The worst part of it all? She's gone missing now and we can't get a hold of her.

She said something about booby trapping this file... muttered something about a killer being after her. She seemed paranoid.

Anyway, can you help us take a look at her alibi and make sure it checks out?

## Hint

1. The binary is compiled with debug symbols.
2. She seemed to say something about setting up a decoy alibi. Can you check if her real alibi is around somewhere?

## Solution
Since the binary is compiled with debug symbols (`-g` flag), we can load it into gdb and disassemble the main function. This will show us two variables: `decoy_idx` and `decoy_salt_idx`.
Printing the values of `real_idx` and `real_salt_idx` will reveal the real indices. We can then cross reference this against the `strings` and `salts` arrays respectively to obtain the flag.

Alternatively, we can also load the program into a decompiler (e.g. IDA Pro, Ghidra, Binary Ninja, etc.). Once we have navigated to the `decoy_idx`  and `decoy_salt_idx` variables in memory,
the `real_idx` and `real_salt_idx` variables can be seen directly below them. Similar to the previous approach, we cross reference these indices with their respective arrays to get the flag.

## Flag
`cssactf{pwn3d_4_susp3ct_4l1b1_1a3z5q7w}`