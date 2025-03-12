# Warped QR Code
- Revision 0
- Forensics

## Description
A fellow detective stumbled upon a clue that is hidden behind a QR. You recieve the pdf but then your friend went off a tangent saying something about how he was using **Windows** and never specified if the file was a word or pdf document. Alas the photo made the selfish decision to not open properly and you aren't sure what is causing the behaviour

## Hints
What does Unix and Windows based system do differently when you write a essay and the next line?

## Solution
Unix based systems use '\n' to let the program know to create a new line. Windows on the other hands adds a cariage return prior to the \n (\r\n). Windows generally autocorrect itself if it only sees \n and inserts it automatically. So it adds \r before \n when it is not suppose to. 

Just create a program that removes the \r and the QR code should show itself properly. There are no \r instances in a pdf file so this makes it much easier
