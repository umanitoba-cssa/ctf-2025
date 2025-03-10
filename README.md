# Literally Empty Evidence

## Description

You got a strange email with a file attached. To your mismay you see nothing but also suspiciously that there is 34 lines. Perhaps this wasn't just a sick prank after all

(Note this does not have the cssactf{} included but the decoded message should be there)

## Hint

Open this document in a code editor and notice how there is a faint pattern of nothing

## Solution

The flag is encoded in Morse Code where each tab (\t) is a -, new line (\n) is . and \* \* is the same. Simply create a program that converts into morse code and run an online compiler to reveal the flag

## Flag

`cssactf{NowYouSeeMeNowYouDont}`

