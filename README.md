# Prime Suspect

## Description

It seems like the suspect learned how to use a 2d array. One step closer to narrowing down the whereabouts of where it could be

## Solution

The code takes each character and takes the unicode value and breaks it down into primes and their exponents. This is the **Fundamental Theorem of arithmetic** (should have learned from Math1240). The data is stored in a 12x30 array where each Column represents a prime and the index the exponent. And each row is the corresponding characters prime decomposition. 

Then for every collumn, every value in each entry is added up. Then the number is converted into a character (Starting at A of course). Repeate this for the remaining columns and that is how we get the output string.


