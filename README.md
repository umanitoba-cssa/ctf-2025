# Spiderman Meme

## Description:

What is this file doing out in the open? 

## Solution

This is a hex string duplicated three times with some minor changes. You should notice that some of the text is not valid hex (such as 7T) but it only exists in one duplication but not the other two. 

So simply split the string into 3 sections, iterate through them and copy over the most common character between the three. Then run through a hex to text converter and reveal the flag

`63 73 73 61 63 74 66 7B 54 72 69 70 6C 65 5F 54 68 72 65 61 74 5F 49 73 5F 42 65 73 74 5F 54 68 72 65 61 74 7D` 
## Flag 

`cssactf{Triple_Threat_Is_Best_Threat}`
