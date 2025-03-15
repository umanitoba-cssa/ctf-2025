# Madame Gene Gripene 2 - The PC Password

- Revision 1
- Cryptography
- Medium 

## Description

Good job - let's get to it then.

My late husband's server is here. He left this note for me, but I haven't been able to get into his server at all. All I know is the person on that note he refers to, he's talked about before, but none of us could find this Eren Egiv. *That name rolls on the tongue.*

Once you're able to login, I'm sure you can use it as a flag for your project. This internship of yours needs some phrase, yes? I'm sure my husband thought of this beforehand.

(Note: The solution must be prefixed with `cssa{` and postfixed with `}` to be a valid flag.)

## Solution

This is a reverse Vigenere cipher, otherwise known as a Beauford cipher. The key is "erenegiv", which is just vigenere backwards. It's a double hint :D

## Flag

cssa{iminmootown}
