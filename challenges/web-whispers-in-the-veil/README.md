# whispers-in-the-veil
- Revision 0
- Web Exploitation
- Medium
- 300 Points

## Description
The murder investigation of tech mogul Daniel Crowe has hit a dead end. While the prime suspect, known online as nexxode, was seen near the scene of the crime, investigators believe they had accomplices—co-conspirators hiding in the digital shadows.

All clues point to VeilChat, a secretive chat platform known for its underground user base. Authorities have identified nexxode as an active user, but without access to their chat history, the case remains unsolved.

Your mission: Hack into VeilChat and uncover the conversations of those in contact with nexxode.

<http://whispers-in-the-veil.ctf.umanitobacssa.ca:30402>

## Hints
- Have the developers left any useful clues behind in the source code of any of the pages?
- Is there anything interesting about how the home page works?

## Solution
The backend code for this challenge is not provided to players, so they have to figure it all out from the HTML alone.

First, the /login.html page includes a note from the site developers which reveals that:
  - The website uses session tokens to track authentication
  - The session token gets stored in the 'session' cookie after login
  - The session token is stored in the 'session_token' attribute in the database
  - The chat interface is located at /chat.html

On the home page, the list of team members displayed on the home page gets dumped out as an array in the Javascript console. Digging deeper, we see that team list is populated by calling the /api/users endpoint:

```
/api/users?include=id,username,title,bio&is_team=1
```

Based on the parameters in the URL that gets called, you can infer that you can request potentially any attribute from the users table and filter on any properties that you want. Since we know session_token is one of the attributes, and can see that username is an attribute, we can construct our own URL to request the session token for the user nexxode:

```
/api/users?include=username,session_token&username=nexxode
```

This will return the session token for the user. Then we can set the 'session' cookie using browser devtools and navigate to the /chat.html page. The user is now logged in, and the flag can be found in the conversation with PhantomPhreak

## Flag
`cssactf{@rb1Tr4rY-atTr!bUt3$-a11oW-aUt#3n7Ic@ti0N-732a1d35}`