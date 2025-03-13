# Short Lived

- Forensics
- Medium
- 250 points

## Description

Hey its a mugshot, I wonder what he could be hiding?

## Solution

If you open an mp4 file in a hex editor, you will see some text on the right side that says mvhd. This specifies the characteristics of the video. For this problem, skipping ahead 12 bytes you will see `E8` This is known as the time unit (1000 units) and the four bytes afterwards describe the video length using the time units. The value set is `0C 1C` (3100 units or 3.1 seconds) and changing the value to a very large number will play the full video and the flag will be shown to you. 

## Flag

`cssactf{Sponsored_by_Raycon}`
