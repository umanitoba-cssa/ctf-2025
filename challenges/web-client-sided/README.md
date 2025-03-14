# client-sided
- Revision 0
- Web Exploitation
- Easy
- 100 Points

## Description
We found a webpage that we believe a criminal is using to coordinate with others. We keep detecting that the contents of the page change weekly, but we have no idea what the password is to view the data. Can you take a look?

## Hints
- Inspect element

## Solution
The password is validated client-side in a Javascript tag on the page. The password is checked in chunks of 4 letters and is 36 characters long. This can be manually put back together pretty quickly:

`gccdgh47js1*bvzb1pkb$!g#$%^b~qgrmdq8`

When you enter the password on the page it will perform a susbtitution cipher to reveal the flag.

## Flag
`cssactf{Au7H-0N-7#E-B@cK3nD-56cb8a6}`