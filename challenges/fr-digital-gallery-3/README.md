# John's Digital Gallery 3
- Revision 0
- Forensics

## Description
Detective! We've received an anonymous tip about the existence of a suspicious establishment called John's Digital Gallery. After investigating, we've recovered several suspicious pictures that seemed to have been tampered with, but we couldn't find any further evidence. Perhaps you could lend us your insight?

John, the owner, described this picture as *quite moving* and *gets better with time*. It just looks like a random picture of a street to me and I don't have time to be staring at this thing. Maybe you can look into the future or something haha and see what he means. Take care of this.

## Solution
The `jpg` is actually `gif` with a really long first frame (about 11 minutes). Find out it's a gif by either the size of the file or reading the header with `hexdump` to find the real type. Then split the gif into frames using a tool or website like `ezgif.com`.

## Flag
`cssactf{m0710n_15_l0710n}`
