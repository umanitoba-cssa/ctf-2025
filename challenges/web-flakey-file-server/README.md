# flakey-file-server
- Revision 0
- Web Exploitation
- Medium
- 200 Points

## Description
We've linked a certain internet user to a recent crime, but we have no idea who is behind the pseudonym. They have been pretty good at covering their tracks and hiding their identity. The only thing we've found is their personal file server. Could you poke around the server and see if there's anything that might tell us who this person is?

<http://flakey-file-server.ctf.umanitobacssa.ca:30403>

## Hints
1. The web server has a certain directory set as the 'base' directory, is there any way we could navigate to directories outside that one?
2. Your browser might prevent you from typing certain characters in a URL, is there another way you can write them?

## Solution
The backend code for this challenge is not provided to players, so they have to figure it all out from the HTML alone.

The backend server will list any directory or provide any file you ask it for, the only catch is the base directory is /files/public. You need to use the relative path specifier `..` to back out of the directory and work your way through the private folder to a photo of a staff ID card. You can use `..` directly in something like Postman without issue, but in a browser URL bar you will need to URL encode very special symbol you want to use, including slashes. The flag can be found at:

`/%2E%2E%2Fprivate%2Fimportant%20documents%2Fstaff%20id.jpg`

which decodes to

`/../private/important documents/staff id.jpg`

## Flag
`cssactf{R3l@t1v3ly-d!reCt3d-15e874bb}`