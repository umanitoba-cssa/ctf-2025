# Prime Suspect
- Revision 0
- Reverse Engineering

## Description

Your final suspect has come up with another encryption system and the for loops tricky, can you crack the puzzle?

## Solution
The code takes each character and takes the unicode value and breaks it down into primes and their exponents. This is the **Fundamental Theorem of Arithmetic** (should have learned from MATH 1240). The data is stored in a 12x16 array where each column represents a prime and the index the exponent. And each row is the corresponding characters prime decomposition. 

Then for every collumn, every value in each entry is added up. Then the number is converted into a character (Starting at A of course). Repeat this for the remaining columns and that is how we get the output string.

### Thought Process

Every number has a **unique** decomposition and it would be wise to pick characters that contain only one prime (for example 'E' would be 4 which decomposed would be $2^2$ Repeat this for the remaining primes and it (hopefully) won't be too tedious to rebuild. 

**Note:** This problem has many solutions since multiplication commutes and you will get the same answer as long as the exponents match up. So there are some checks to make sure there is (hopefully) only one unique answer.

- 'A' would not affect the output string since 'A' is mapped to one which is not prime. 
- There are many duplicate letters so to make it easier to reverse engineer and also to remove PP having affecting the same as Ia
- Having the sum add up to 958 would fix certain letters in place

## Flag

cssactf{CEIIMPPQQSSo}
// Prob won't include because it is more (tedious) guesswork than real reverse engineering 
