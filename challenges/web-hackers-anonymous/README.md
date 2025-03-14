# hackers-anonymous
- Revision 1
- Web Exploitation
- Hard
- 400 Points

## Description
Detective, we have a lead. The primary suspect in a high-profile murder case, Lucas Vance, had the perfect alibi - too perfect. His travel records, rental agreements, and even financial transactions all check out… except they were forged. Someone expertly altered the digital records to shift the blame onto an innocent party.

Our forensics team uncovered an anonymous cryptocurrency transaction between Lucas and a hacker-for-hire service known as Hackers Anonymous. We’ve linked the payment to a specific username on their underground marketplace, but that's not enough - without solid proof that the hacker was hired to forge documents, our case won't hold up in court.

We need you to break into Hackers Anonymous and find the job request that links a user by the name of **voidwalker** to the crime. Can you find a way to break into his account and check his job history?

Unfortunately we couldn't find the full source code for the server software online, but we were able to leak a diff for a recent commit from their git server. They quickly patched the hole before we could dump the full repository, so hopefully there's something in this diff that exposes a vulnerability you can exploit.

<https://hackers-anonymous.ctf.umanitoba.ca:30401>

## Hints
1. You need to break into an account, is there anything notable about the authentication mechanism?
2. Does the website provide some way to login to an account if we don't have the password?
3. The password and the account recovery token must be stored somewhere for them to validate it, is there any vulnerability that can help leak or interfere with that data?

Additional hints if very few teams are able to solve the challenge late into the CTF:

4. This might be a helpful resource: <https://ctf101.org/web-exploitation/sql-injection/what-is-sql-injection/>
5. *Provide the full index.js source file*

## Solution
There is a SQL injection vulnerability in the login API endpoint, the query for the user doesn't use a proper prepare statement to insert the username.

In addition to this, the recover account mechanism requires the user to enter a valid username first before moving to the account recovery page. The account recovery page displays the entered username which is populated from the result of the user lookup in the login endpoint.

Combining the exploit with the data output, we can leak the account recovery token for any user we want. For voidwalker we can enter this in the username field, then press "recover account":

`' UNION select recovery_token as username, password from users WHERE username='voidwalker'; --`

It's necessary to rename the recovery_token field as the backend retrieves this from the JSON object by name.

This brings us to the recover account page and what normally would show the username will now instead show the recovery token for the account. We can enter this into the prompt and voila, we are logged in as voidwalker.

### Alternative Solution

Using the SQL injection vulnerability you can select a constant value into a column and rename it to anything you want. This means you can make the query return the username voidwalker but inject any password you wish. Since the backend validates the password using bcrypt you will need to generate a valid bcrypt string as the constant, plaintext won't work.

For example, enter this under the username field and enter `password` for the password, then press login:

`' UNION select 'voidwalker' as username, '$2a$12$ylc9SX/CGr2GRp9CQCE3vezVndIUMkj2aeTg8mmxkolNS4AjzRXmi' as password; --`

### Alternative Solution

It's not impossible to imagine that the flag is probably stored in one of the fields for one of the jobs in the database, so with a little trial and error you can use the SQL injection vulnerability to pull the flag into the recovery page directly:

`' UNION select jobs.details AS username, 'a' AS password FROM jobs WHERE jobs.details LIKE '%cssactf%'; --`

## Flag
`cssactf{pR3p@reD-1Nj3c7!0nS-@N0nYm0Us-f9e07432}`