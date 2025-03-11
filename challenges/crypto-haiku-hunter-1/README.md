# Haiku Hunter - The First Riddle

* Revision 0
* Cryptography
* Easy

## Description

Attention, citizens of Winnipeg! A lunatic referring to themself as the "Haiku Hunter" has struck! A victim was found with a strange encrypted note pinned to their chest. The only clue to decode it might be in this haiku left at the scene:

    Matching keys unlock
    Opposites tighten the door
    Truth lies in sameness
    
The encrypted note is attached. Can you decode it and find what message the killer left behind?

## Solution

The haiku contains clues about XOR encryption:

* "Matching keys unlock" - A bit XOR'd with itself gives 0, an "opened" door
* "Opposites tighten the door" - Again, a bit XOR'd with the other gives 1, a "closed" door
* "Truth lies in sameness" - "sameness" is the key, also (albeit a reach) the solution lies in XOR-ing the encrypted message with the key

The message, when decrypted, looks like:

```markdown
Dear Detective,

You've found my first riddle. Not bad, but the game has just begun.
If you're clever enough to read this, then perhaps you'll survive long enough to catch me.

My first victim was wearing a mask like everyone else.
But unlike others, they were hiding something more sinister.
I simply revealed their true nature.

Your reward for solving this puzzle:
cssactf{x0r_m4sks_th3_truth}

Happy hunting,
- The Haiku Hunter
```

## Flag

`cssactf{x0r_m4sks_th3_truth}`

## Implementation Details

`message.bin` was generated with the following code:

```python
def xor_encrypt(message, key):
    encrypted = bytearray()
    for i in range(len(message)):
        encrypted.append(message[i] ^ key[i % len(key)])
    return encrypted

# The message containing our flag
message = """
Dear Detective,

You've found my first riddle. Not bad, but the game has just begun.
If you're clever enough to read this, then perhaps you'll survive long enough to catch me.

My first victim was wearing a mask like everyone else.
But unlike others, they were hiding something more sinister.
I simply revealed their true nature.

Your reward for solving this puzzle:
cssactf{x0r_m4sks_th3_truth}

Happy hunting,
- The Haiku Hunter
"""

# Using "sameness" as the key (from the haiku)
key = b"sameness"

encrypted = xor_encrypt(message.encode(), key)

# Save to file
with open("files/message.bin", "wb") as f:
    f.write(encrypted)
```

A sample solution to decrypt the file may look like the following:

```python
def xor_decrypt(encrypted, key):
    decrypted = bytearray()
    for i in range(len(encrypted)):
        decrypted.append(encrypted[i] ^ key[i % len(key)])
    return decrypted

# Read the encrypted file
with open("encrypted_note.bin", "rb") as f:
    encrypted = f.read()

# Try the key "sameness" from the haiku
key = b"sameness"
decrypted = xor_decrypt(encrypted, key)

# Print the decrypted message
print(decrypted.decode())
```

Note that knowledge of `bytearray()` should be unnecessary; it is sufficient to have something like the following:

```python
def xor_decrypt(encrypted, key):
    decrypted = []
    for i in range(len(encrypted)):
        decrypted.append(encrypted[i] ^ key[i % len(key)])
    return decrypted

# Read the encrypted file
with open("files/message.bin", "rb") as f:
    encrypted = f.read()

# Try the key "sameness" from the haiku
key = b"sameness"
decrypted = xor_decrypt(encrypted, key)

# Print the decrypted message
for i in range(len(decrypted)):
    print(chr(decrypted[i]), end="")
```