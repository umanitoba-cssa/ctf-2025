# steganography-3
- Revision 0
- Forensics

## Description

## Solution
The `jpg` is actually `gif` with a really long first frame (about 11 minutes). Find out it's a gif by either the size of the file or reading the header with `hexdump` to find the real type. Then split the gif into frames using a tool or website like `ezgif.com`.

## Flag
`cssactf{m0710n_15_l0710n}`
