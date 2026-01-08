# CSSA CTF 2025 Challenge Repository

You can generate the challenge.yml files for each challenge by installing a package and running the script:
```bash
pip install pyyaml 
python yml-maker.py
```

## Challenge README Format

**Note:** You can use either `-` or `*` for bullet points in the metadata section (Information under Challenge Name).

Each challenge must have a README.md file that follows this format:

```markdown
# Challenge Name
- Revision 0
- Category Name
- Difficulty
- Point Value Points
- Type: standard (optional)
- State: visible (optional)
- Flag Type: static (optional)

## Description
This is the challenge description that participants will see.
Can include multiple paragraphs, links, connection instructions, etc.

## Hints
1. First hint
2. Second hint
3. Third hint

## Solution
This section contains the solution and will NOT be included in challenge.yml.
Explain how to solve the challenge here.

## Flag
`cssactf{YourFlagHere}`
```

### Required Sections
- **First line**: Challenge name (used as the challenge title in CTFd)
- **Category**: Must be one of: Binary Exploitation, Web Exploitation, Cryptography, Forensics, Reverse Engineering, Misc, OSINT, Pwn, Steganography (if more categories are added, they should be added in the script)
- **Difficulty**: Easy, Medium, or Hard (becomes a tag in CTFd)
- **Points**: Number followed by "Points" (e.g., "100 Points")
- **## Description**: Challenge description shown to participants
- **## Flag**: The flag enclosed in backticks

### Optional Sections
- **## Hints**: Will be appended to the description if present
- **Type**: `standard` (fixed points) or `dynamic` (decreasing points) - defaults to `standard`
- **State**: `visible` (shown immediately) or `hidden` (hidden until revealed) - defaults to `visible`
- **Flag Type**: `static` (exact match), `regex` (pattern matching), or `case_insensitive` - defaults to `static`

### Script Defaults (if not found in README)
- **Category**: Defaults to `Misc`
- **Points**: Defaults to `100`
- **Difficulty**: Defaults to `Medium`
- **Description**: Empty string
- **Flag**: Empty string
- **Type**: Defaults to `standard`
- **State**: Defaults to `visible`
- **Flag Type**: Defaults to `static`

### Script Hardcoded Values
- **Author**: Always set to `CSSA` (configured at top of yml-maker.py)
- **Files**: Automatically includes all files from the `files/` subdirectory in each challenge folder

### Example (with optional fields)

```markdown
# Parity the Platypus
- Revision 0
- Cryptography
- Easy
- 100 Points
- Type: standard
- State: visible
- Flag Type: static

## Description
Dear Detective,

I finished creating a program that should help remove some tedious work in detective work and the program has been encrypted and sent as binary. Unfortunately, I learned that an evil-doer has blasted it with their least-significant-bit-flip-inator and the program won't decrypt anymore.

Luckily, I have a failsafe mechanism implemented where the 8th bit from the left (1st bit from the right) must be 1 if the number of 1s is odd and 0 if the number of 1s is even. Perhaps if we figure out which 8-bit words were affected (and no longer pass the failsafe), we can actually gain information about this evil-doer! I have split up the program into lines of 8-bits for ease of digestion.

I await your reply,
P.P.

## Hints
1. Look up "parity bit" to understand the error detection mechanism
2. The affected bits reveal the flag when converted to ASCII

## Solution
Calculate the parity and see which lines don't match and were thus affected. Alternatively, calculate the opposite, or even odd 1s parity and see which lines *do* match. Convert those binary numbers to ASCII characters to obtain the flag.

## Flag
`cssactf{Bit_By_Bit_I_Weep}`
```