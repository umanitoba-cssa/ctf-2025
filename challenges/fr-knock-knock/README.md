# The Knock-Knock Killer

* Revision 0
* Forsenics
* Easy

## Description

Idea provided by Rob Guderian (thanks Rob).

The notorious "Knock-Knock Killer" has been terrorizing the city of Ravenholm for months, leaving a trail of precisely arranged crime scenes and cryptic messages. Detective Sarah Miller has been tracking this methodical serial killer across three brutal murders, growing increasingly desperate as the pattern suggests a fourth victim is imminent.

Each victim was found in a carefully staged tableau, with peculiar marks on door frames suggesting the killer announces their presence with a specific sequence of knocks before entering. Neighbors have reported hearing these distinctive knocks, but never in their entirety.

After investigating the third murder scene yesterday, Detective Miller discovered a weathered leather-bound journal hidden beneath a floorboard. The journal appears to belong to the killer and contains this chilling entry written in meticulous handwriting:

> *"My work begins when the clock strikes twelve and darkness reigns supreme. The first announcement of my presence shall come at port 3712, when the stars align and the moon casts no shadow.*
> 
> *Each knock brings me closer to my masterpiece. The sequence must be perfect, or the ritual fails.*
> 
> *Tonight, I will complete what I started. The next victim has been chosen. Their door awaits my touch."*

The journal entry abruptly ends there. Detective Miller believes that by following the killer's knock pattern, she might intercept crucial information about the next victim's location or identity. The department's cyber forensics unit has detected unusual network traffic from what they believe is the killer's command server.

The clock is ticking. Can you help Detective Miller decode the knock sequence and potentially save a life before midnight strikes again? Navigate to the killer's server at running at `<server_ip>`, if you can find your way...

## Solution

This challenge implements a sequential port knocking mechanism where each correct knock reveals the next port in the sequence. Unlike traditional port knocking where all ports must be known in advance, this version requires players to discover ports one at a time.

### Analysis:
1. The description reveals the first port to knock on: 3712
2. Each successful knock returns a message containing the next port to try
3. The final knock returns the flag

### Step-by-step Solution:

1. **First Knock - Starting Point**:
   The description reveals that the first port to knock on is 3712.

   ```bash
   # First knock - revealed in the initial description
   nc -u <server_ip> 3712
   ```
   
   Response: "As you investigate the first location, you find a note: 'Dawn breaks at 5917, when the jogger counts his steps.'"

2. **Second Knock - Following the Trail**:
   The response from the first knock indicates that the next port is 5917.

   ```bash
   # Second knock - discovered from the first knock's response
   nc -u <server_ip> 5917
   ```
   
   Response: "The second crime scene reveals another message: 'The final secret awaits at 8821, as the church bells ring at dusk.'"

3. **Final Knock - Uncovering the Truth**:
   The second knock reveals the final port: 8821.

   ```bash
   # Final knock - discovered from the second knock's response
   nc -u <server_ip> 8821
   ```
   
   Response: The flag `cssactf{kn0ck_kn0ck_th3_k1ll3r_w45_h3r3}`

### Python Solution Script:
```python
import socket
import time

def send_knock(ip, port):
    """Send a UDP knock to the specified port and return the response"""
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(5)
    
    print(f"Knocking on port {port}...")
    sock.sendto(b"knock", (ip, port))
    
    try:
        data, _ = sock.recvfrom(1024)
        response = data.decode()
        print(f"Response: {response}")
        return response
    except socket.timeout:
        print("No response received (timeout)")
        return None
    finally:
        sock.close()

def follow_the_trail(ip, first_port):
    """Follow the trail of ports by knocking sequentially"""
    current_port = first_port
    
    # First knock
    response = send_knock(ip, current_port)
    if not response:
        print("Investigation failed at the first location")
        return
    
    # Extract second port from response (5917 from the clue)
    if "5917" in response:
        current_port = 5917
    else:
        print("Failed to find next port in the response")
        return
    
    time.sleep(1)  # Brief pause between knocks
    
    # Second knock
    response = send_knock(ip, current_port)
    if not response:
        print("Investigation failed at the second location")
        return
    
    # Extract third port from response (8821 from the clue)
    if "8821" in response:
        current_port = 8821
    else:
        print("Failed to find final port in the response")
        return
    
    time.sleep(1)  # Brief pause between knocks
    
    # Final knock
    response = send_knock(ip, current_port)
    if not response:
        print("Investigation failed at the final location")
        return
    
    print("\nInvestigation complete!")
    if "cssactf{" in response:
        print(f"Flag found: {response}")

if __name__ == "__main__":
    server_ip = input("Enter the server IP: ")
    follow_the_trail(server_ip, 3712)
```

If any knock is performed out of sequence or on an incorrect port, the server responds with an error message and resets the sequence, requiring the player to start over from the first port.

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