# Corrupt Files Department 1
- Revision 0
- Forensics
- Easy

## Description
Your junior detective has really outdone themselves again. This time, you are handed the piece of evidence in-person since they can no longer trust technology. However, it appears that their child may have gotten ahold of it. Maybe you can salvage what little is left of the **QR code** by fixing it up? It feels like it's going to be a long day at work...

## Hints
1. Is you device recognizing the the QR code?
2. What does your device need to recognize the QR code?
      
## Solution
QR codes are actually extremely robust to modifications. What really matters are the three squares. Open the QR code in an image editor, and put three clean squares where the old ones should be. The QR code should now be scannable and brings you to a website containing the flag.

## Flag
cssactf{Three_Squares_Best_Squares}
