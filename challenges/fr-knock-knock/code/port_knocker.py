#!/usr/bin/env python3
import socket
import threading
import time
import sys
import signal

# Configuration
LISTENING_IP = "0.0.0.0"  # Listen on all interfaces
KNOCK_SEQUENCE = [3712, 5917, 8821]  # Knock sequence
KNOCK_TIMEOUT = 30 # Seconds before knock sequence resets
FLAG = "cssactf{kn0ck_kn0ck_th3_k1ll3r_w45_h3r3}"

# Track active knock sequences by client IP
knock_state = {}
lock = threading.Lock()

# Clues to provide after each knock - now with math puzzles
NEXT_CLUES = [
    "As you investigate the first location, you find a bloodstained note with a puzzle:\n\n'To find where I'll be at dawn, solve this riddle of life and death:\nTake the number of victims found so far,\nMultiply by the length of my knock pattern,\nAdd the product to the number of fingers on both my hands plus one more,\nThen multiply by the square of the first perfect number,\nMultiply by the number of digits in an ASCII value,\nAdd the largest number that is not the sum of any number of distinct squares,\nFinally, subtract the number of lines in this puzzle.'\n\nDetective Miller mumbles, 'This twisted mind thinks murder is just a game...'",
    
    "The second crime scene reveals another mathematical message scratched into the wall:\n\n'My final performance requires precision. Find me where:\nThe sum of all single-digit prime numbers,\nMultiplied by the product of the first 3 Fibonacci numbers after 1,\nDivided by the smallest perfect number,\nAdded by the number of letters in \"KNOCK KNOCK KILLER\",\nMultiplied by the ASCII value of 'K',\nAdded by the number whose first two digits are the number of ways to arrange the letters in 'KILL',\nAnd whose last two digits are the number of primes between 1 and 200.'\n\nA chill runs down your spine as you realize time is running out...",
    
    FLAG  # The final response is the flag itself
]

def signal_handler(sig, frame):
    print("Shutting down server...")
    sys.exit(0)

def cleanup_thread():
    """Periodically clean up expired knock sequences"""
    while True:
        time.sleep(1)
        current_time = time.time()
        with lock:
            expired_ips = []
            for ip, (sequence, timestamp) in knock_state.items():
                if current_time - timestamp > KNOCK_TIMEOUT:
                    expired_ips.append(ip)
            
            for ip in expired_ips:
                del knock_state[ip]
                print(f"[*] Sequence for {ip} expired")

def handle_knock(port):
    """Create a socket listening for UDP "knocks" on the specified port"""
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((LISTENING_IP, port))
    print(f"[+] Listening for knocks on port {port}")
    
    while True:
        data, addr = sock.recvfrom(1024)
        client_ip = addr[0]
        print(f"[*] Received knock from {client_ip} on port {port}")
        
        with lock:
            current_time = time.time()
            
            # If this IP isn't in our state dict or has timed out, initialize it
            if client_ip not in knock_state or current_time - knock_state[client_ip][1] > KNOCK_TIMEOUT:
                knock_state[client_ip] = ([], current_time)
            
            sequence, _ = knock_state[client_ip]
            next_port_index = len(sequence)
            
            # Check if this is the expected port in the sequence
            if next_port_index < len(KNOCK_SEQUENCE) and port == KNOCK_SEQUENCE[next_port_index]:
                sequence.append(port)
                knock_state[client_ip] = (sequence, current_time)
                
                # Send the next clue/port
                print(f"[+] {client_ip} knocked correctly on port {port}. Progress: {len(sequence)}/{len(KNOCK_SEQUENCE)}")
                
                # Send the appropriate clue based on their progress
                next_clue = NEXT_CLUES[next_port_index]
                sock.sendto(next_clue.encode(), addr)
                
                # If they've completed the sequence, reset for them
                if len(sequence) == len(KNOCK_SEQUENCE):
                    print(f"[+] {client_ip} completed the full knock sequence! Flag sent.")
                    del knock_state[client_ip]
            else:
                # Wrong sequence, reset
                print(f"[!] Incorrect knock from {client_ip} on port {port}, resetting")
                knock_state[client_ip] = ([], current_time)
                sock.sendto(b"Wrong door... The killer's trail has gone cold. Start again at the beginning.", addr)

def main():
    signal.signal(signal.SIGINT, signal_handler)
    
    # Start the cleanup thread
    cleanup = threading.Thread(target=cleanup_thread, daemon=True)
    cleanup.start()
    
    # Create a thread for each port in the knock sequence
    threads = []
    for port in set(KNOCK_SEQUENCE):  # Use set to avoid duplicate ports
        thread = threading.Thread(target=handle_knock, args=(port,), daemon=True)
        thread.start()
        threads.append(thread)
    
    print("[+] Port knocker server started")
    print(f"[+] Listening for the sequence: {KNOCK_SEQUENCE}")
    
    # Keep the main thread alive
    for thread in threads:
        thread.join()

if __name__ == "__main__":
    main()