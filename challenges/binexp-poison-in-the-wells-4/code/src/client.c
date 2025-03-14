/*
 * Copyright (c) 2025 Intl. Bank of Fairstone Capital and Asset Management
 * All Rights Reserved. Do Not Distribute.
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
#include <stdbool.h>

// All usernames MUST be 15 characters, plus one for the null terminator.
// This is a technical limitation with our filesystem, so we just rear-pad the username with zeroes.
#define USERNAME_LENGTH 16
#define MAX_PASSWORD_LENGTH 64

typedef struct {
    bool authenticated;
    char username[USERNAME_LENGTH];
    char balancePath[256];
    char transactionsPath[256];
} UserData;

UserData authenticated_user;

bool (*functionPtr)(void);
bool auth_gate(bool (*functionPtr)(void));
void init(void);
void process_input();
bool balance(void);
bool transactions(void);
bool load_user_password(char username[USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]);

int main(void)
{
    init();

    while (1)
    {
        process_input();
    }

    return 0;
}

void process_input()
{
    char command[MAX_PASSWORD_LENGTH];
    char username[USERNAME_LENGTH];
    
    printf("\nEnter a command: ");
    gets(command);

    printf("\n");

    if (strncmp(command, "help", 4) == 0)
    {
        printf("Commands:\n");
        printf("  login [username] - Login to your bank account\n");
        printf("  list - List customers with an account at this branch\n");
        printf("  help - Display this help message\n");
        printf("  exit - Exit the program\n");
        printf("Commands requiring authentication:\n");
        printf("  balance - View your account balance\n");
        printf("  transactions - View your transactions for the last 30 days\n");
        printf("  logout - Sign out of your bank account\n");
    }
    else if (strncmp(command, "exit", 4) == 0)
    {
        printf("Exiting program\n");
        exit(0);
    }
    else if (strncmp(command, "login", 5) == 0) {
        strncpy(username, command + 6, USERNAME_LENGTH);
        login(username);
    }
    else if (strncmp(command, "list", 4) == 0)
    {
        list_customers();
    }
    else if (strncmp(command, "balance", 7) == 0)
    {
        auth_gate(balance);
    }
    else if (strncmp(command, "transactions", 12) == 0)
    {
        auth_gate(transactions);   
    }
    else if (strncmp(command, "logout", 6) == 0)
    {
        authenticated_user.authenticated = false;
        printf("You have been signed out.\n");
    }
    else
    {
        printf("Unknown command - type 'help' for a list of commands\n");
    }
}

bool auth_gate(bool (*functionPtr)(void)) {
    char buffer[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    bool success = false;
    
    if (!authenticated_user.authenticated) {
        printf("You must be logged in to perform this action.\n");
        return;
    }

    printf("Please re-enter your password for account ");
    printf(authenticated_user.username);
    printf(": ");

    success = load_user_password(authenticated_user.username, password);

    if (!success) {
        printf("An error occurred while attempting to authenticate your account.\n");
        return;
    }

    fgets(buffer, sizeof(buffer), stdin);

    if (strncmp(buffer, password, strlen(password)) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    return (*functionPtr)();
}

bool balance() {
    system(authenticated_user.balancePath);
    return true;
}

bool transactions() {
    system(authenticated_user.transactionsPath);
    return true;
}

void list_customers() {
    DIR *d;
    struct dirent *dir;
    char buffer[256];
    int length = 0;
    d = opendir("./users");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            strcpy(buffer, dir->d_name);
            if (buffer[0] == '.') {
                continue;
            }

            for (int i = 0; i < strlen(buffer); i++) {
                if (buffer[i] == '0') {
                    buffer[i] = '\0';
                    break;
                }
            }
            printf("%s\n", buffer);
        }
        closedir(d);
    }
}

void pad_username(char username[USERNAME_LENGTH]) {
    for (int i = 0; i < strlen(username); i++) {
        if (!isalnum(username[i])) {
            username[i] = '0';
        }
    }

    for (int i = strlen(username); i < USERNAME_LENGTH-1; i++) {
        username[i] = '0';
    }
    username[USERNAME_LENGTH] = '\0';
}

bool load_user_password(char username[USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./users/%s.txt", username);

    fflush(stdout);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        return false;
    }

    char buffer[MAX_PASSWORD_LENGTH];

    if (!fgets(buffer, MAX_PASSWORD_LENGTH, file)) {
        fclose(file);
        return false;
    }
    
    fclose(file);

    strcpy(password, buffer);

    return true;
}

void login(char username[USERNAME_LENGTH]) {
    UserData userData;
    char buffer[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    if (authenticated_user.authenticated) {
        printf("You are already logged into an account. Please logout first.\n");
        return;
    }

    userData.authenticated = false;
    pad_username(username);
    strcpy(userData.username, username);

    load_user_password(username, password);

    printf("Authenticating as '%s'\n", username);
    printf("Please enter your password: ");
    gets(buffer);    
    
    if (strncmp(buffer, password, strlen(password)) == 0) {
        userData.authenticated = true;
        snprintf(userData.balancePath, 255, "cat ./balances/%s.txt", userData.username);
        snprintf(userData.transactionsPath, 255, "cat ./transactions/%s.txt", userData.username);
        printf("Transactions path %s\n", userData.transactionsPath);
        authenticated_user = userData;
        printf("Authentication successful, welcome %s!\n", userData.username);
    } else {
        printf("Incorrect password.\n");
    }
}

/**
 * @brief Initialize the program.
 *
 * Display the welcome message and authenticated user information.
 */
void init(void)
{
    printf("INTERNATIONAL BANK OF FAIRSTONE CAPITAL\n");
    printf("Type 'help' for help.\n");
}