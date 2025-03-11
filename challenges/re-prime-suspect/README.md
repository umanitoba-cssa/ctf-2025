# Prime Suspect
- Revision 0
- Reverse Engineering

## Description
It seems like the suspect learned how to use a 2d array. One step closer to narrowing down the whereabouts of where it could be

## Solution
The code takes each character and takes the unicode value and breaks it down into primes and their exponents. This is the **Fundamental Theorem of Arithmetic** (should have learned from MATH 1240). The data is stored in a 12x16 array where each column represents a prime and the index the exponent. And each row is the corresponding characters prime decomposition. 

Then for every collumn, every value in each entry is added up. Then the number is converted into a character (Starting at A of course). Repeat this for the remaining columns and that is how we get the output string.

### Thought Process

Every number has a **unique** decomposition and it would be wise to pick characters that contain only one prime (for example 'E' would be 4 which decomposed would be $2^2$ Repeat this for the remaining primes and it (hopefully) won't be too tedious to rebuild. 

**Note:** that the character 'A' does not affect the output string if it is appended as it value is 1 which is neither prime nor composite (an assumption the FTOA has). Meaning that if you have less than 12 characters, adding 'A' will suffice
