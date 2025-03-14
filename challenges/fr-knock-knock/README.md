# The Knock-Knock Killer

* Revision 1
* Forsenics
* Medium

## Description

Idea provided by Rob Guderian (thanks Rob).

The notorious "Knock-Knock Killer" has been terrorizing the city of Ravenholm for months, leaving a trail of precisely arranged crime scenes and cryptic messages. Detective Sarah Miller has been tracking this methodical serial killer across three brutal murders, growing increasingly desperate as the pattern suggests a fourth victim is imminent.

Each victim was found in a carefully staged tableau, with peculiar marks on door frames suggesting the killer announces their presence with a specific sequence of knocks before entering. Neighbors have reported hearing four knocks at a time, but they aren't sure what happened next.

After investigating the third murder scene yesterday, Detective Miller discovered a weathered leather-bound journal hidden beneath a floorboard. The journal appears to belong to the killer and contains this chilling entry written in meticulous handwriting:

> *"My work begins when the clock strikes twelve and darkness reigns supreme. The first announcement of my presence shall come at port 3712, when the stars align and the moon casts no shadow.*
> 
> *Each knock brings me closer to my masterpiece. The sequence must be perfect, or the ritual fails.*
> 
> *Tonight, I will complete what I started. The next victim has been chosen. Their door awaits my touch."*

The journal entry abruptly ends there. Detective Miller believes that by following the killer's knock pattern, she might intercept crucial information about the next victim's location or identity. The department's cyber forensics unit has detected unusual network traffic from what they believe is the killer's command server.

The clock is ticking. Can you help Detective Miller decode the knock sequence and potentially save a life before midnight strikes again? Navigate to the killer's server running at `<server_ip>`, if you can find your way...

## Solution

This challenge implements a sequential port knocking mechanism where each correct knock reveals a mathematical puzzle that must be solved to determine the next port in the sequence.

### Analysis:
1. The description reveals the first port to knock on: 3712
2. Each successful knock returns a mathematical puzzle that must be solved to discover the next port
3. The final knock returns the flag

### Mathematical Puzzle Solutions:

#### First Knock (3712):
The first port is revealed directly in the killer's journal entry.

#### Second Knock (5917) - Solution to first puzzle:
The puzzle requires these steps:
1. Take the number of victims found so far (3)
2. Multiply by the killer's knock pattern length (4): 3 × 4 = 12
3. Add the product to fingers on both hands plus one more (11): 12 + 11 = 23
4. Multiply by the square of the first perfect number (6²): 23 × 36 = 828
5. Multiply by the number of digits in an ASCII value (7): 828 × 7 = 5796
6. Add the largest number that is not the sum of any number of distinct squares (128): 5796 + 128 = 5924
7. Subtract the number of lines in the puzzle (7): 5924 - 7 = 5917

This gives us port 5917.

#### Final Knock (8821) - Solution to second puzzle:
The puzzle requires these steps:
1. Sum of all single-digit prime numbers (2+3+5+7) = 17
2. Multiply by the product of first 3 Fibonacci numbers after 1 (2×3×5) = 17 × 30 = 510
3. Divide by the smallest perfect number (6) = 510 ÷ 6 = 85
4. Add the number of letters in "KNOCK KNOCK KILLER" (16) = 85 + 16 = 101
6. Multiply by the ASCII value of 'K' (75) = 101 × 75 = 7575
7. Add the number whose first two digits are the number of different ways to arrange the letters in "KILL" (12) = 7575 + 1200 = 8775
8. Add the number of primes between 1 and 200 (46) = 8775 + 46 = 8821

This gives us port 8821.

### Step-by-step Solution:

1. **First Knock - Starting Point**:
   The description reveals that the first port to knock on is 3712.

   ```bash
   # First knock - revealed in the initial description
   nc -u <server_ip> 3712
   ```
   
   This returns a mathematical puzzle.

2. **Second Knock - Solving the First Puzzle**:
   Solve the mathematical puzzle to discover that the next port is 5917.

   ```bash
   # Second knock - discovered by solving the first puzzle
   nc -u <server_ip> 5917
   ```
   
   This returns another mathematical puzzle.

3. **Final Knock - Solving the Second Puzzle**:
   Solve the second mathematical puzzle to discover that the final port is 8821.

   ```bash
   # Final knock - discovered by solving the second puzzle
   nc -u <server_ip> 8821
   ```
   
   Response: The flag `cssactf{kn0ck_kn0ck_th3_k1ll3r_w45_h3r3}`

Note: The server internally implements a 30 second timeout. If the timeout is exceeded, the player will have to restart from the first port, but the riddles stay the same.

## Flag

`cssactf{kn0ck_kn0ck_th3_k1ll3r_w45_h3r3}`

## Setup

1. Install the files located in `code/`
2. Navigate to the directory with the located files
3. Build the Docker container:
```bash
docker build -t port-knocker .
```
4. Run the Docker container and start the required ports
```bash
docker run -p 3712:3712/udp -p 5917:5917/udp -p 8821:8821/udp port-knocker
```
5. **Ensure the correct server IP is given in the problem description at deployment!**

## Implementation Details

Python's `socket` module was used to implement the server. The code can be located in [port_knocker.py](./code/port_knocker.py).

The Dockerfile to build the challenge can also be located in [Dockerfile](./code/Dockerfile).