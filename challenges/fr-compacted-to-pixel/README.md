# Compacted to Pixel

- Forensics
- Medium
- 250 points
  
## Description

You only have one more QR code left to investigate. It appears to be a single pixel and you aren't sure what to do about it. 


## Solution

The photo size has been **intentionally** limited by a hex editor. If you search up `ff c0` the following bytes control some properties of the photo to render on screen. The relevant bytes are the 4th and 5th, and 6th and 7th after `c0` They control the image height and width. Setting the value to a very large number and opening the image you shoud see Caway holding the flag in front of you
