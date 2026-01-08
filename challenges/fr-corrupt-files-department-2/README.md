# Corrupt Files Department 2
- Revision 0
- Forensics
- Easy

## Description
Welcome to the Corrupt Files Department, you think in your head. Earlier today, your junior detective handed you a piece of evidence that they had clumsily opened and saved in **Windows** with some jank **text editor** program to save as a **PDF** file, messing it up even when you use a **Linux** system like a righteous detective would. Perhaps it's still saveable after some tinkering, so you unfurl your eyebrows and get to work.

## Hints
1. What do *nix systems and Windows systems do differently specifically with text editing?

## Solution
*nix systems use `\n` to denote a newline wheres Windows use `\r\n`. Create a program that removes unnecessary `\r` characters.

## Flag
cssactf{Backslash_r_Backslash_n}
