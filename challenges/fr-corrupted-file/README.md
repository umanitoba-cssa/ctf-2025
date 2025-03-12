# Corrupted File
- Revision 0
- Forensics

## Description
Your fellow detective has shined again providing evidence in the form of a QR code. This time he doesn't trust windows anymore and decides to give it to you in person. Unfortunately when you scan the QR code, you aren't able to open it as a too many dectective pins caused pencil sized poked holes in the QR code. And two of the squares has been hastly scribbled for some reason

## Hints
  1. **Don't Overthink!** This (hopefully) doesn't require any sternography tools
  2. What does every QR code have in common and how robust are QR codes error correction?
      
## Solution
The only components of the QR code that matters are the three squares. So what you can do is open the photo in an image editor, copy the untouched square (in the top right) and copy and paste over the 2 overdrawn squares. The qr should be scannable

Note there is a hidden image zipped in but it is a red herring and leads to a rickroll ;)
