# Empty Evidence
- Revision 0
- Cryptography

## Description
You receive a strange email with a file attached. To your dismay, you see that it contains nothing. However, you notice that, suspiciously, there are 34 lines. Perhaps this wasn't just a sick prank after all? Follow this empty trail to get to the answer.

> Answer isn't in "cssactf{...}" format but simply enter your answer as if it were contained by "cssactf{...}".

## Solution
The flag is encoded in Morse Code where each tab `\t` is a `-`, new line `\n` is `.` and ` ` is the same. Simply create a program that converts into Morse Code and run an online compiler to reveal the flag.

## Flag
`cssactf{NowYouSeeMeNowYouDont}`
