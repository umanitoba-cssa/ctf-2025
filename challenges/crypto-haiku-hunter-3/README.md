# Haiku Hunter - The Third Riddle

* Revision 0
* Cryptography
* Medium

## Description

The Haiku Hunter's third victim has been discovered - a librarian found dead amidst scattered puzzle pieces. Once again, a haiku was left at the scene:

    Scattered pieces wait
    Each fragment yearns for its place
    Order hides in words
    
Along with the haiku, a strange encoded message was found. Stranger still, a lengthy letter was discovered nearby that seems to contain the Haiku Hunter's manifesto. The detectives believe the key to decoding the message lies somewhere within this text.

## Solution

The manifesto in `manifesto.txt` reads:

*I grew up as the twenty-third child in a broken home. My father left when I was six, my mother struggled with her demons until I turned nine. By fifteen, I knew I was different. Others saw chaos in the world, but I saw patterns everywhere. The fourteen steps leading to my childhood school seemed random to most, but I recognized the sequence they formed.*

*At thirty-two, I discovered my purpose. While others saw meaningless violence in the news, I recognized order in the madness. The seven victims of the Crystal Lake murders spoke to me through the patterns of their deaths. By twenty, I had begun collecting books on cryptography and puzzles.*

*My first kill came at thirty-nine, after watching my target for sixteen days. Everything must be exact, every piece must fit. My second victim spent five years teaching without seeing the formula of their own demise. The twelve signs were there, but they failed to notice.*

*I chose my fourtieth target for their eight years arranging books while failing to arrange their own fate. The nineteen clues I left were ignored. Perhaps you, detective, can see what they could not. The four corners of this puzzle might reveal my design.*

*I spent thirty minutes arranging this message. Twenty-nine words in the haiku - each carefully selected. The fourty-first truth remains hidden unless you understand the thirty-fifth principle of my work. Finding the twenty-seventh key will unlock more than just this message.*

*Eleven more shall join my collection before my masterpiece is complete. The three patterns you seek are hidden in plain sight. Look for the twenty-second sign when the next body appears. The seventeen syllables of the haiku aren't arbitrary - nothing I do is by thirty-four chance.*

*The thirteenth hour approaches. Can you solve my puzzle before the twenty-first victim falls? I'll leave eighteen more breadcrumbs for you to follow. The forty-two paths before you both lead to the twenty-sixth truth. My pattern reaches completion at thirty-seven.*

*I have watched you for ten days now, detective. The twenty-fifth move is yours to make. Every twenty-fourth word is significant, as is the thirty-first decision you'll soon face. Will you see the thirty-eight sign, or remain blind like the others?*

*The twenty-eighth piece completes this section of our game. Thirty-six hours remain before I strike again. I am always a step ahead, like in a game of thirty-three chess pieces.*

The challenge requires understanding the "Jigsaw Puzzle" obfuscation technique. The haiku provides clues:

* "Scattered pieces wait" - Suggests pieces of data that have been scattered or shuffled
* "Each fragment yearns for its place" - Indicates that each piece has a correct position
* "Order hides in words" - Hints that the ordering information is hidden in the text

The manifest contains exactly the same number of written-out numbers as there are characters in the encoded flag. These numbers represent the original positions of each character in the encoded flag.

To solve this challenge:

1. Extract all the numbers from the manifest (written in words)
2. Use these numbers as indices to rearrange the scrambled flag characters

The numbers in the manifest are:
- twenty-third (23)
- six (6)
- nine (9)
- fifteen (15)
- fourteen (14)
- thirty-two (32)
- seven (7)
- twenty (20)
- first (1)
- thirty-nine (39)
- sixteen (16)
- second (2)
- five (5)
- twelve (12)
- fourtieth (40)
- eight (8)
- nineteen (19)
- four (4)
- thirty (30)
- twenty-nine (29)
- fourty-first (41)
- thirty-fifth (35)
- twenty-seventh (27)
- eleven (11)
- three (3)
- twenty-second (22)
- seventeen (17)
- thirty-four (34)
- thirteenth (13)
- twenty-first (21)
- eighteen (18)
- forty-two (42)
- twenty-sixth (26)
- thirty-seven (37)
- ten (10)
- twenty-fifth (25)
- twenty-fourth (24)
- thirty-first (31)
- thirty-eight (38)
- twenty-eighth (28)
- thirty-six (36)
- thirty-three (33)

When this solution is applied to the encoded flag, it reveals:
`cssactf{j1gs4w_puzzl3_r3v34ls_my_1d3nt1ty}`

## Flag

`cssactf{j1gs4w_puzzl3_r3v34ls_my_1d3nt1ty}`

## Implementation Details

The prose was generated with Claude 3.7 Sonnet Thinking, and edited to ensure each number appears only once and reduce potential confusion. The prose is then put into `manifesto.txt`.

The flag was scrambled using the following algorithm:

```python
def create_jigsaw_puzzle(flag_content):
    indices = [
        23, 6, 9, 15, 14, 32, 7, 20, 1, 39,
        16, 2, 5, 12, 40, 8, 19, 4, 30, 29, 41,
        35, 27, 11, 3, 22, 17, 34, 13, 21, 18,
        42, 26, 37, 10, 25, 24, 31, 38, 28, 36, 33
    ]
    
    # Create the scrambled flag using these indices
    scrambled = ''
    for idx in indices:
        scrambled += flag_content[idx]
    
    # Return both the scrambled flag and the indices that map back to original positions
    # Add 1 to each index for 1-based indexing in the prose
    return scrambled, [i+1 for i in indices]
    
flag_content = "cssactf{j1gs4w_puzzl3_r3v34ls_my_1d3nt1ty}"
scrambled, positions = create_jigsaw_puzzle(flag_content)

# Save the scrambled flag to a file
with open("files/flag.txt", "w") as f:
    f.write(scrambled)
```

The scrambled flag is stored in `flag.txt`, and the numbers in the prose correspond to the original positions of each character.

Sample Python solution:

```python
def solve_jigsaw(scrambled_flag, positions):
    # Create an array to hold the unscrambled flag
    original_flag = [''] * len(scrambled_flag)
    
    # Place each character from the scrambled flag in its original position
    for i, pos in enumerate(positions):
        # Adjust for zero-indexing
        original_flag[pos-1] = scrambled_flag[i]
    
    # Join the characters back into a string
    return ''.join(original_flag)

# The scrambled flag from the encoded file
with open("flag.txt", "r") as f:
    scrambled_flag = f.read().strip()

# The positions extracted from the manifest (in order of appearance)
positions = [
    23, 6, 9, 15, 14, 32, 7, 20, 1, 39,
    16, 2, 5, 12, 40, 8, 19, 4, 30, 29, 41,
    35, 27, 11, 3, 22, 17, 34, 13, 21, 18,
    42, 26, 37, 10, 25, 24, 31, 38, 28, 36, 33
]

# Solve the puzzle
flag_content = solve_jigsaw(scrambled_flag, positions)
print(f"{flag_content}")
```
