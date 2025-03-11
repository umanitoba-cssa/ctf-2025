# Haiku Hunter - The Second Riddle

* Revision 0
* Cryptography
* Medium

## Description

The Haiku Hunter has claimed another victim! This time, a mathematics professor was found in their office with yet another encrypted message. Alongside the body was a small note containing this haiku:

    Tiny change's the name
    Each step depends on the last
    First truth starts the path
    
The police have recovered the encrypted file, but it appears the Haiku Hunter has upgraded their encryption method. Can you decode this message and find the clue left behind?

## Solution

The haiku contains clues about Delta Encoding:

* "Tiny change's the name" - "Delta" is the name of the encryption method
* "Each step depends on the last" - Each value depends on the previous value (the core concept of delta encoding)
* "First truth starts the path" - The first byte is stored directly and begins the sequence

Delta encoding works by:

1. Storing the first byte directly
1. For each subsequent byte, storing the difference (delta) between it and the previous byte

To decode, we start with the first byte, then add each delta to get the next byte in sequence.

The decrypted message reveals:

```
Dear Detective,

You've solved my second puzzle. Your persistence is admirable.

My second victim was a mathematics professor who believed everything 
had an elegant formula. He spent his life teaching students that 
complex problems could be broken down into simple steps.

Ironic, isn't it? He couldn't see the simple pattern in his own life.
The pattern that led me to him.

Your reward for understanding the sequence:
cssactf{d3lt4_3nc0d1ng_r3v34ls_th3_p4tt3rn}

Two down, more to go.

- The Haiku Hunter
```

## Flag

`cssactf{d3lt4_3nc0d1ng_r3v34ls_th3_p4tt3rn}`

## Implementation Details

`message.bin` was generated with the following code:

```python
def delta_encode(message):
    if not message:
        return b""
    
    encoded = bytearray()
    encoded.append(message[0])  # Store first byte directly
    
    # For each subsequent byte, store the delta from previous byte
    for i in range(1, len(message)):
        # Calculate difference and handle potential underflow with modulo
        delta = (message[i] - message[i-1]) % 256
        encoded.append(delta)
    
    return encoded

# The message containing our flag
message = """
Dear Detective,

You've solved my second puzzle. Your persistence is admirable.

My second victim was a mathematics professor who believed everything 
had an elegant formula. He spent his life teaching students that 
complex problems could be broken down into simple steps.

Ironic, isn't it? He couldn't see the simple pattern in his own life.
The pattern that led me to him.

Your reward for understanding the sequence:
cssactf{d3lt4_3nc0d1ng_r3v34ls_th3_p4tt3rn}

Two down, more to go.

- The Haiku Hunter
"""

encoded = delta_encode(message.encode())

# Save to file
with open("files/message.bin", "wb") as f:
    f.write(encoded)
```

The solver will need to recognize the delta encoding pattern from the haiku clues and implement the decoding algorithm to recover the original message and extract the flag.

A sample solution may look like the following:

```python
def delta_decode(encoded):
    if not encoded:
        return b""
    
    decoded = bytearray()
    decoded.append(encoded[0])  # First byte is stored directly
    
    # For each subsequent byte, add the delta to the previous value
    for i in range(1, len(encoded)):
        # Use modulo 256 to handle overflow correctly
        next_byte = (decoded[i-1] + encoded[i]) % 256
        decoded.append(next_byte)
    
    return decoded

# Read the encoded file
with open("message.bin", "rb") as f:
    encoded = f.read()

decoded = delta_decode(encoded)
print(decoded.decode())
```