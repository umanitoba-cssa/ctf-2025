/*
 * Copyright (c) 2023 Tesla Inc.
 * All Rights Reserved.
 *
 * This software is the proprietary information of Tesla Inc.
 * Viewing this document is prohibited under any circumstances.
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

#define PASS_SIZE 32

char filepath[256];
int month = 0;
int year = 0;

int start_message(void);
void process_input(void);
int get_user_authorization(const char *username);
int check_user_authorization(int min_level);
int parse_month_year(const char *command);
int get_summary(void);
int get_details(void);
int get_current_year(void);
int get_current_month(void);

int get_current_year() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    return tm_info->tm_year + 1900;  // tm_year is years since 1900
}

int get_current_month() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    return tm_info->tm_mon + 1;  // tm_mon is months since January
}

int main(void)
{
    start_message();

    while (1)
    {
        process_input();
    }

    return 0;
}

/**
 * @brief Read a command from the terminal and execute the corresponding action.
 *
 * The following commands are available:a64l
 *   help - Display a help message
 *   list [category] - List available documents in the specified category (public, secure, logs)
 *   view [document-id] - View the specified document
 *   exit - Exit the program
 */
void process_input()
{
    char command[32];
    printf("\nEnter a command: ");
    gets(command);

    printf("\n");

    if (strcmp(command, "help") == 0)
    {
        printf("Available commands:\n");
        printf("  summary [month] [year] - View summary of transactions made at this dealership in the given month\n");
        printf("  details [month] [year] - View full details of transactions made at this dealership in the given month\n");
        printf("  help - Display this help message\n");
        printf("  exit - Exit the program\n");
    }
    else if (strcmp(command, "exit") == 0)
    {
        printf("Exiting program\n");
        exit(0);
    }
    else if (strncmp(command, "summary", 7) == 0)
    {
        if (!parse_month_year(command)) {
            return;
        }

        get_summary();
    }
    else if (strncmp(command, "details", 7) == 0)
    {
        if (!parse_month_year(command)) {
            return;
        }

        snprintf(filepath, 200, "./details/%02d-%04d.csv", month, year);

        if (check_user_authorization(2) == 0) {
            return;
        }

        get_details();
    }
    else
    {
        printf("Unknown command. Type 'help' for a list of available commands.\n");
    }
}

/**
 * @brief Get the user authorization level from the database.
 */
int get_user_authorization(const char *username) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./users/%s.txt", username);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("User not found, defaulting to lowest authorization level");
        return 0;
    }

    int value = 0;
    char buffer[2]; // Enough to hold a single digit + null terminator
    if (fgets(buffer, sizeof(buffer), file)) {
        if (isdigit(buffer[0])) {
            value = buffer[0] - '0'; // Convert char to int
        }
    }

    fclose(file);
    return value;
}

int check_user_authorization(int min_level) {
    char* username = getenv("USER");
    int auth_level = get_user_authorization(username);

    if (auth_level < min_level) {
        printf("You do not have permission to access this data.\n");
        return 0;
    }

    printf("PASS");

    return 1;
}

//eg. "summary 01 2021" or "details 01 2021". There may be other arguments after the month and year.
int parse_month_year(const char *command) {
    char month_str[3];
    char year_str[5];
    
    if (sscanf(command, "%*s %2s %4s", month_str, year_str) != 2) {
        printf("Could not read month/date.'.\n");
        return 0;
    }

    month = atoi(month_str);
    year = atoi(year_str);

    if (month > get_current_month() - 1) {
        printf("Data not yet available.\n");
        return 0;
    }

    if (month < 1) {
        printf("Invalid month.\n");
        return 0;
    }

    if (year < get_current_year()) {
        printf("Data for previous years have been archived and must be accessed through the Financial Archive tool. Please contact an administrator for assistance.\n");
        return 0;
    }

    if (year > get_current_year()) {
        printf("Data not yet available.\n");
        return 0;
    }

    return 1;
}

int get_summary() {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./summary/%02d-%04d.csv", month, year);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Data not found for month %02d, year %04d.\n", month, year);
        return 0;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 1;
}


int get_details() {    
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Data not found for month %02d, year %04d.\n", month, year);
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
 * @brief Display the number of available documents to the terminal.
 *
 * The following directories are checked:
 *   ./public (and one level of subdirectories)
 *   ./secure (and one level of subdirectories)
 *   ./logs
 *
 * The final output will be three lines, each displaying the number of files in the respective directory.
 * The file counts of subdirectories are counted into the overall total of the parent directory and not
 * displayed separately.
 */
int start_message(void)
{

    printf("Tesla Inc. Sales Tracker\n");

    char* username = getenv("USER");
    int auth_level = get_user_authorization(username);

    printf("Authenticated User: %s\n", username);
    printf("Authorization Level %d\n\n", auth_level);

    return auth_level;
}