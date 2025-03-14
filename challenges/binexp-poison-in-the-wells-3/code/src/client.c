/*
 * Copyright (c) 2025 Broker Data Services Inc.
 * All Rights Reserved.
 *
 * This software is the proprietary information of Broker Data Services Inc. and its partners.
 */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

#define MAX_FIELD_LENGTH 64

char filepath[256];
char business_id[256];

typedef struct {
    char name[MAX_FIELD_LENGTH];
    char passphrase[MAX_FIELD_LENGTH];
} User;

void init(void);
void process_input();
void get_user_data(User* data);
int check_user_authorization(int min_level);
int parse_business_id(const char *command);
int get_registration(void);
int get_contacts(void);

int main(void)
{
    init();

    while (1)
    {
        process_input();
    }

    return 0;
}

/**
 * @brief Read a command from the terminal and execute the corresponding action.
 *
 * The following commands are available:
 *   help - Display a help message
 *   list - Display a list of registered businesses
 *   view [business-id] - Show summary details of a business
 *   contacts [business-id] - Show details of a business including contact information and addresses
 *   exit - Exit the program
 */
void process_input()
{
    char command[MAX_FIELD_LENGTH];
    char user_passphrase[MAX_FIELD_LENGTH];

    User userData;
    get_user_data(&userData);
    
    printf("\nEnter a command: ");
    fgets(command, sizeof(command), stdin);

    printf("\n");

    if (strncmp(command, "help", 4) == 0)
    {
        printf("Available commands:\n");
        printf("  list - Display a list of registered businesses\n");
        printf("  view [business-id] - Show summary details of a business\n");
        printf("  contacts [business-id] - Show details of a business including contact information and addresses\n");
        printf("  help - Display this help message\n");
        printf("  exit - Exit the program\n");
    }
    else if (strncmp(command, "exit", 4) == 0)
    {
        printf("Exiting program\n");
        exit(0);
    }
    else if (strncmp(command, "list", 4) == 0) {
        get_list();
    }
    else if (strncmp(command, "view", 4) == 0)
    {
        if (!parse_business_id(command)) {
            return;
        }

        snprintf(filepath, 200, "./registrations/%s.txt", business_id);

        display_file();
    }
    else if (strncmp(command, "contacts", 8) == 0)
    {
        if (!parse_business_id(command)) {
            return;
        }

        printf("Please enter your passphrase to access sensitive information: ");
        
        fgets(user_passphrase, MAX_FIELD_LENGTH, stdin);
        if (strcmp(user_passphrase, userData.passphrase) != 0) {
            printf("Incorrect passphrase.\n");
            return;
        }

        snprintf(filepath, 200, "./contacts/%s.txt", business_id);

        display_file();
    }
    else
    {
        printf("Unknown command: '");
        printf(command);
        printf("' - type 'help' for a list of commands\n");
    }
}

/**
 * @brief Retrieve user data from the file system.
 *
 * The user's name and passphrase are read from a file named after the user's username.
 *
 * @param data Pointer to a User structure to store the retrieved data.
 */
void get_user_data(User* data) {
    memset(data, 0, sizeof(User));

    char* username = getenv("USER");

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./users/%s.txt", username);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("User not found, abort.");
        exit(0);
    }

    char buffer[MAX_FIELD_LENGTH];

    if (!fgets(buffer, MAX_FIELD_LENGTH, file)) {
        perror("Error reading user passphrase");
    }

    strcpy(data->name, username);
    strcpy(data->passphrase, buffer);

    fclose(file);
}

/**
 * @brief Parse the business ID from the command.
 *
 * The business ID is extracted from the command string.
 *
 * @param command The command entered by the user.
 * @return 1 if the business ID was successfully parsed, 0 otherwise.
 */
int parse_business_id(const char *command) {
    char id_str[12];
    
    if (sscanf(command, "%*s %11s", id_str) != 1) {
        printf("Could not read business ID.'.\n");
        return 0;
    }

    strcpy(business_id, id_str);

    return 1;
}

/**
 * @brief Display a list of registered businesses.
 *
 * The list of businesses is read from a file and displayed to the terminal.
 *
 * @return 1 if the list was successfully displayed, 0 otherwise.
 */
int get_list() {
    FILE *file = fopen("./list.txt", "r");
    if (!file) {
        printf("Data not found for business with ID %s.\n", business_id);
        return 0;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 1;
}

/**
 * @brief Display the contents of a file.
 *
 * The file path is specified by the global variable 'filepath'.
 *
 * @return 1 if the file was successfully displayed, 0 otherwise.
 */
int display_file() {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Data not found for business with ID %s.\n", business_id);
        return 0;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 1;
}

/**
 * @brief Initialize the program.
 *
 * Display the welcome message and authenticated user information.
 */
void init(void)
{
    printf("HUB INTERNATIONAL: BUSINESS REGISTRATION DATABASE\n");

    char* username = getenv("USER");

    printf("Authenticated User: %s\n", username);
}