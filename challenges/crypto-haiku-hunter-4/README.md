# Haiku Hunter - The Final Riddle

* Revision 0
* Cryptography
* Hard

## Description

The Haiku Hunter's reign of terror is nearing its climax! A senior cryptographer was found dead in a locked room with only a computer displaying an encrypted file and a final haiku:

    Armor shields the truth
    Words wear masks of other words
    First keys hide the last

The computer contains an encrypted file and a peculiar document titled "cipher.txt" that appears to be a translation dictionary of some kind - each line contains a common English word. There's also a sticky note with the number "1337" written on it.

Forensics revealed that the victim was working on advanced cryptographic algorithms. Their recent browser history shows research on military-grade encryption standards and ancient substitution techniques.

This could be our last chance to stop the Haiku Hunter before their "masterpiece" is complete. Decrypt the message and end this nightmare once and for all.

## Solution

This challenge combines two advanced obfuscation techniques: AES encryption and a Jargon translation table.

The haiku provides key clues:
* "Armor shields the truth" - Refers to AES (Advanced Encryption Standard), commonly used by military/defense
* "Words wear masks of other words" - Hints at the translation table (Jargon method)
* "First keys hide the last" - Suggests that part of the AES key is hidden and must be brute-forced

The solution requires multiple steps:

### Step 1: Understanding the Translation Table
The file `cipher.txt` contains 256 common English words, arranged in specific order. This is a translation table where each word represents a byte value (0-255). The encrypted message has been converted to these words.

### Step 2: Converting Words Back to Bytes
First, we need to convert the obfuscated text back to bytes using the translation table:

```python
def words_to_bytes(words, translation_table):
    result = bytearray()
    for word in words:
        if word in translation_table:
            byte_value = translation_table.index(word)
            result.append(byte_value)
    return bytes(result)

# Read the translation table
with open("cipher.txt", "r") as f:
    translation_table = [line.strip() for line in f.readlines()]

# Read the obfuscated message
with open("encrypted.txt", "r") as f:
    obfuscated_text = f.read().strip()

# Split the text into words and convert to bytes
words = obfuscated_text.split()
encrypted_bytes = words_to_bytes(words, translation_table)
```

### Step 3: AES Decryption with Partial Key
The sticky note with "1337" is a hint about the AES key. We need to construct a key where "1337" is the seed for a key generation algorithm, but the last two bytes need to be brute-forced:

```python
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
import hashlib
import struct

def derive_base_key(seed):
    # Create a key from the seed, but leave last 2 bytes for brute-forcing
    key_base = hashlib.sha256(str(seed).encode()).digest()[:-2]
    return key_base

def try_decrypt(encrypted_data, key, iv):
    try:
        cipher = AES.new(key, AES.MODE_CBC, iv)
        decrypted = unpad(cipher.decrypt(encrypted_data), AES.block_size)
        # Check if the decrypted text looks like readable text
        # For example, check if it contains mostly printable ASCII
        if all(32 <= b <= 126 or b in (10, 13) for b in decrypted):
            return decrypted
    except Exception:
        pass
    return None

# Extract IV (first 16 bytes)
iv = encrypted_bytes[:16]
encrypted_data = encrypted_bytes[16:]

# Get base key from the seed 1337
base_key = derive_base_key(1337)

# Brute force the last 2 bytes
for i in range(65536):  # 2^16 possibilities for 2 bytes
    last_bytes = struct.pack(">H", i)  # Convert integer to 2 bytes
    full_key = base_key + last_bytes
    
    result = try_decrypt(encrypted_data, full_key, iv)
    if result:
        print(f"Found key! Last bytes: {i}")
        print(result.decode())
        break
```

When successful, this reveals the final message from the Haiku Hunter:

```
Dear Detective,

You've reached the end of our little game. I must admit, I'm impressed by your persistence and intellect.

You've proved yourself worthy of knowing the truth. I am not a random killer - I am a hunter of those who abuse knowledge and power. Each victim was carefully chosen for their crimes against humanity, hidden beneath respectable facades.

The cryptographer you thought was my latest victim? They developed surveillance systems that have been used to oppress innocent people across the globe. Their algorithms have led to countless disappearances, all while they lived in comfort and accolades.

My work is now complete. The patterns I've created have served their purpose - drawing attention to these hidden atrocities while testing if anyone in authority had the skills to see through the veil.

You've passed that test. Now it's your choice what to do with this knowledge.

The flag you seek: cssactf{m4st3r_0f_l4y3r3d_3ncrypt10n_4nd_0bfusc4t10n}

Will you continue to hunt me, knowing what you now know? Or will you become a hunter of truth yourself?

The choice is yours.

- The Haiku Hunter
```

## Flag

`cssactf{m4st3r_0f_l4y3r3d_3ncrypt10n_4nd_0bfusc4t10n}`

## Implementation Details

### Creating the translation table

The translation table was (anticlimatically) pulled from the [top 10000 most common English words](https://github.com/david47k/top-english-wordlists/blob/master/top_english_words_lower_10000.txt), without shuffling.

### Encrypting the Message

```python
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import hashlib
import struct
import random

def bytes_to_words(data, translation_table):
    words = []
    for byte in data:
        words.append(translation_table[byte])
    return " ".join(words)

def derive_key(seed, last_bytes):
    # Generate key using seed, with specific last 2 bytes
    key_base = hashlib.sha256(str(seed).encode()).digest()[:-2]
    return key_base + last_bytes

# Original message
message = """Dear Detective,

You've reached the end of our little game. I must admit, I'm impressed by your persistence and intellect.

You've proved yourself worthy of knowing the truth. I am not a random killer - I am a hunter of those who abuse knowledge and power. Each victim was carefully chosen for their crimes against humanity, hidden beneath respectable facades.

The cryptographer you thought was my latest victim? They developed surveillance systems that have been used to oppress innocent people across the globe. Their algorithms have led to countless disappearances, all while they lived in comfort and accolades.

My work is now complete. The patterns I've created have served their purpose - drawing attention to these hidden atrocities while testing if anyone in authority had the skills to see through the veil.

You've passed that test. Now it's your choice what to do with this knowledge.

The flag you seek: cssactf{m4st3r_0f_l4y3r3d_3ncrypt10n_4nd_0bfusc4t10n}

Will you continue to hunt me, knowing what you now know? Or will you become a hunter of truth yourself?

The choice is yours.

- The Haiku Hunter
"""

# Read the translation table
with open("files/cipher.txt", "r") as f:
    translation_table = [line.strip() for line in f.readlines()]

# AES Encryption
seed = 1337
last_bytes = struct.pack(">H", 42069)  # Specific value for last 2 bytes
key = derive_key(seed, last_bytes)
iv = bytes([random.randint(0, 255) for _ in range(16)])  # Random IV

# Encrypt
cipher = AES.new(key, AES.MODE_CBC, iv)
encrypted_data = cipher.encrypt(pad(message.encode(), AES.block_size))

# Prepend IV to encrypted data
full_encrypted = iv + encrypted_data

# Convert to words using translation table
obfuscated_text = bytes_to_words(full_encrypted, translation_table)

# Save the obfuscated text
with open("files/encrypted.txt", "w") as f:
    f.write(obfuscated_text)
```

Solution code is listed above.