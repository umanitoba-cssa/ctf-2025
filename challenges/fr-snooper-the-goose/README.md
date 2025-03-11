# Snooper the Goose
- Revision 0
- Forensics
- Medium

## Description
Winnipeg. March 15, 1990... you're sitting in your dimly lit, smoke filled office. Suddenly, "you've got mail" blasts through a tiny pc speaker. Mail. You open the email up to find... a picture? No other context, no subject line, no body, and from an unknown sender. But it's different. Not spam. You reckon there's something hidden deep in the picture, so you put on your hat and trenchcoat. It's detective time.

## Hint
You might want to use `stegsolve` or `steghide`.

## Solution
Enter `steghide extract -sf *.jpeg` and you will notice it is locked behind a passphrase. To find the passphrase, open the image in a hex editor and at the bottom of the file, it will say `A SNOOPER` which is the passphrase.
