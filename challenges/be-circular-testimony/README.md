# The Circular Testimony

* Revision 0
* Binary Exploitation
* Easy

## Description

Idea provided by Rob Guderian (thanks Rob).

Detective Miles has been investigating the notorious "Circular Killer" for months. The murderer is known for arranging victims in a circular pattern and leaving cryptic messages written in code at each crime scene.

After interviewing a key witness who glimpsed the killer's latest message, Detective Miles recorded the testimony in his custom digital recorder—a device he designed himself. But when reviewing the notes later, something strange happened: only fragments of the witness's account were visible, and what might be crucial evidence seems to have disappeared.

Miles needs your help to recover the complete testimony, which might contain information about the killer's identity or their next target. Can you exploit the device's memory bug and reveal the hidden message before the killer strikes again?

## Solution

When we examine the program's code, we find that Detective Miles's custom recorder uses a circular buffer for storing testimony. The key vulnerability is in how the device handles memory when displaying stored data.

The program's memory management has several key features:
1. The buffer initially contains a partial testimony ("THE_KILLER") followed by what appears to be a delimiter (null byte)
2. After this delimiter, the rest of the testimony (including the flag) is hidden
3. The device manages memory using two internal pointers: one for reading data (`read_ptr`) and one for writing new data (`write_ptr`)
4. When new testimony is added, the writing pointer advances, and if it would overwrite data that hasn't been "read" yet, the reading pointer also advances
5. The bug is in the display function: it only shows text up to the first null byte, missing any content beyond it

### Step-by-step Solution:

1. First, run the program and check what testimony is currently visible:
   ```
   === DIGITAL TESTIMONY RECORDER ===
   1. Add new testimony
   2. Review current testimony
   3. Exit
   Choice: 2
   
   --- TESTIMONY EXCERPT ---
   THE_KILLER
   ------------------------
   ```
   Notice you only see part of the testimony, not the full message with the evidence.

2. The rest of the testimony (containing the flag) is hidden after a null byte delimiter. To see it, you need to manipulate the device's internal reading pointer.

3. You can exploit the buffer's circular nature by adding enough new testimony to force the reading pointer to advance past the initial data and delimiter.

4. Since the buffer has a size of 128 bytes, and the initial visible testimony plus delimiter takes up 10 bytes, you need to add enough text to push the reading pointer forward to that position:
   ```
   === DIGITAL TESTIMONY RECORDER ===
   1. Add new testimony
   2. Review current testimony
   3. Exit
   Choice: 1
   Enter additional testimony details: [LONG STRING OF CHARACTERS]
   Testimony recorded.
   ```

5. The input should be long enough to fill the buffer and cause the internal reading pointer to advance past the initial visible portion. However, inputting too many characters may overwrite the flag itself. The model input will have 98 characters (as the flag has 30 characters).

6. Now check the testimony again:
   ```
   === DIGITAL TESTIMONY RECORDER ===
   1. Add new testimony
   2. Review current testimony
   3. Exit
   Choice: 2
   
   --- TESTIMONY EXCERPT ---
   cssactf{c1rcul4r_buff3r_l34k} // and whatever else the user inputted
   ------------------------
   ```

7. You've now revealed the hidden evidence!

## Flag

`cssactf{c1rcul4r_buff3r_l34k}`

## Implementation Details

### circular_testimony.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128
#define MAX_INPUT 1024

// The circular buffer
char buffer[BUFFER_SIZE];

// Read and write pointers for the buffer
int read_ptr = 0;
int write_ptr = 0;

// Initialize the buffer with some initial data
void initialize_buffer() {
    // First clear the entire buffer
    memset(buffer, 0, BUFFER_SIZE);
    
    // Set up the initial message (visible to the user)
    const char* initial_message = "THE_KILLER";
    int msg_len = strlen(initial_message);
    
    // Copy the message to the buffer
    for (int i = 0; i < msg_len; i++) {
        buffer[i] = initial_message[i];
    }
    
    // Add a null terminator after the initial message
    buffer[msg_len] = '\0';
    
    // The write pointer starts after the null
    write_ptr = msg_len + 1;
    
    // Hide the flag after the null terminator
    // This won't be visible when printing normally because of the null
    const char* hidden_flag = "cssactf{c1rcul4r_buff3r_l34k}";
    
    // Copy the flag into the buffer after the null
    strcpy(buffer + write_ptr, hidden_flag);
    
    // Reset write_ptr to point after the flag
    write_ptr += strlen(hidden_flag);
    
    // Ensure the rest of the buffer contains null bytes
    for (int i = write_ptr; i < BUFFER_SIZE; i++) {
        buffer[i] = '\0';
    }
    
    // Start reading from the beginning of the buffer
    read_ptr = 0;
}

// Add data to the circular buffer
void add_to_buffer() {
    char input[MAX_INPUT];
    printf("Enter additional testimony details: ");
    
    // Read input
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        printf("Error recording testimony.\n");
        return;
    }
    
    // Remove trailing newline
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
        len--;
    }
    
    // Add each character to the buffer
    for (size_t i = 0; i < len; i++) {
        // Write to the current write position
        buffer[write_ptr] = input[i];
        
        // Move the write pointer forward
        write_ptr = (write_ptr + 1) % BUFFER_SIZE;
        
        // If we're about to overwrite unread data, move the read pointer too
        if (write_ptr == read_ptr) {
            read_ptr = (read_ptr + 1) % BUFFER_SIZE;
        }
    }
    
    // Add null termination at the current write position
    // This is the vulnerability - it doesn't handle proper null termination
    // for a circular buffer
    buffer[write_ptr] = '\0';
    
    printf("Testimony recorded.\n");
}

// Dump the contents of the buffer
void dump_buffer() {
    printf("\n--- TESTIMONY EXCERPT ---\n");
    
    // Print from read pointer to the next null byte
    // This is incorrect for a circular buffer but creates the vulnerability
    printf("%s\n", buffer + read_ptr);
    
    printf("------------------------\n");
}

// Display the menu
void show_menu() {
    printf("\n=== DIGITAL TESTIMONY RECORDER ===\n");
    printf("1. Add new testimony\n");
    printf("2. Review current testimony\n");
    printf("3. Exit\n");
    printf("Choice: ");
}

int main() {
    int choice;
    
    // Initialize the buffer
    initialize_buffer();
    
    printf("Detective Miles' Digital Testimony Recorder v1.0\n");
    printf("The Circular Killer case - CONFIDENTIAL\n");
    printf("Warning: Memory corruption detected in previous sessions.\n");
    printf("Some testimony data may be inaccessible.\n");
    
    while (1) {
        show_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid command. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        // Clear input buffer
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                add_to_buffer();
                break;
                
            case 2:
                dump_buffer();
                break;
                
            case 3:
                printf("Shutting down recorder. Remember, time is running out.\n");
                return 0;
                
            default:
                printf("Unknown command. Please try again.\n");
        }
    }
    
    return 0;
}

```

### Compilation Instructions:
```bash
clang -o circular_testimony circular_testimony.c -Wall # or gcc
```