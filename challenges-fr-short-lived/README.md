# Short Lived

- Forensics
- Medium
- 250 points

## Description

Hey its a mugshot, I wonder what he could be hiding?

## Solution

The Video is a mp4 file which in a hex editor Has bytes that indicate **duration**. More specifically at The the hex 'mvhd' indicates info about the video and 12 bytes later is where it modifies the video length. `E8` is the time unit (1000 in this case) and next 4 indicate the length. The current value is `0C 1C` (3100) or 3.1 seconds but setting the time to anything above 8 seconds will play the full video and have Caway show the flag to you.

## Flag

`cssactf{Sponsored_by_Raycon}`
