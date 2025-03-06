/*
 * Copyright (c) 2001 SecuRITE(tm)
 * All Rights Reserved.
 *
 * This software is the proprietary information of SecuRITE.
 * Use is subject to license terms.
 *
 * Unauthorized copying, modification, distribution, or use of this
 * software, via any medium, is strictly prohibited except as authorized
 * by SecuRITE.
 */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <limits.h>

#define PASS_SIZE 32

typedef struct
{
    char *id;
    char *name;
    char *path;
    char *category;
} Document;

void start_message(void);
Document **list_documents(char *);

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
    char command[1024];
    printf("\nEnter a command: ");
    gets(command);

    printf("\n");

    if (strcmp(command, "help") == 0)
    {
        printf("Available commands:\n");
        printf("  help - Display this help message\n");
        printf("  list [category] - List available documents in the specified category (public, secure, logs)\n");
        printf("  view [document-id] - View the specified document\n");
        printf("  exit - Exit the program\n");
    }
    else if (strcmp(command, "exit") == 0)
    {
        printf("Exiting program\n");
        exit(0);
    }
    else if (strncmp(command, "list", 4) == 0)
    {
        list_command(command);
    }
    else if (strncmp(command, "view", 4) == 0)
    {
        view_command(command);
    }
    else
    {
        printf("Unknown command. Type 'help' for a list of available commands.\n");
    }
}

/**
 * @brief View the contents of the specified document.
 *
 * The document ID must be specified. If no document ID is specified, an error message will be displayed.
 *
 * @param input The command entered by the user.
 *
 * @note The document ID is used to locate the document file. The file contents are then displayed to the terminal.
 */
void view_command(char *input)
{
    char *doc_id = strtok(input, " ");
    if (doc_id == NULL)
    {
        printf("Error: No document ID specified\n");
        return;
    }

    char *doc_id_value = strtok(NULL, " ");
    if (doc_id_value == NULL)
    {
        printf("Error: No document ID specified\n");
        return;
    }

    // Identify the category by the first letter of the folder. Then use list_documents to get a list of
    // documents and their IDs. Then use the ID to get the path of the document and print it.

    Document *document = NULL;
    Document **docs = NULL;
    if (doc_id_value[1] == '-')
    {
        if (doc_id_value[0] == 'S')
        {
            docs = list_documents("./secure");
        }
        else if (doc_id_value[0] == 'P')
        {
            docs = list_documents("./public");
        }
        else if (doc_id_value[0] == 'L')
        {
            docs = list_documents("./logs");
        }
    }
    else
    {
        printf("Error: Document not found\n");
        return;
    }

    if (docs == NULL)
    {
        printf("Error listing documents\n");
        return;
    }

    for (int i = 0; docs[i] != NULL; i++)
    {
        if (strcmp(docs[i]->id, doc_id_value) == 0)
        {
            document = docs[i];
            break;
        }
    }

    if (document == NULL)
    {
        printf("Error: Document not found\n");
        return;
    }

    if (strcmp(document->category, "secure") == 0)
    {
        print_secure_document(document);
    }
    else
    {
        print_document(document);
    }

    for (int i = 0; docs[i] != NULL; i++)
    {
        free(docs[i]->id);
        free(docs[i]->name);
        free(docs[i]->path);
        free(docs[i]->category);
        free(docs[i]);
    }
    free(docs);
}

/**
 * @brief Print the contents of the specified secure document to the terminal.
 *
 * A password must be entered to view the contents of a secure document.
 * The password will be stored in 'passwords/[document-id].pass'.
 *
 * @param document The document to display.
 * 
 * @note Right now the server software requires passwords to be exactly 32 characters long, so we can
 *       assume that the password is 32 characters long. Kinda dumb, probably shouldn't hardcode this, but...
 *       oh well, it should be fine! I'll set PASS_SIZE to 32 and call it a day.
 */
void print_secure_document(Document *document)
{
    char correct_password[PASS_SIZE];
    // I'll just double the size of this one to be safe, 64 characters should be enough.
    // Otherwise if someone accidentally types a few extra characters they would overflow the buffer!
    char entered_password[PASS_SIZE * 2]; 

    char password_file[1024];
    snprintf(password_file, sizeof(password_file), "passwords/%s.pass", document->id);

    FILE *fp = fopen(password_file, "r");
    int i = 0;

    if (fp == NULL)
    {
        printf("Error opening password file!\n");
        return -1;
    }

    for (i = 0; i < PASS_SIZE; i++)
    {
        correct_password[i] = fgetc(fp);
    }
    fclose(fp);

    printf("DOCUMENT ID: %s\n", document->id);
    printf("DOCUMENT NAME: %s\n", document->name);
    printf("DOCUMENT CATEGORY: %s\n\n", document->category);
    printf("An access password is set for this file. Enter it now to view the file.\n");
    printf("Enter the password: ");
    gets(entered_password);
    printf("\n");

    if (memcmp(correct_password, entered_password, PASS_SIZE) == 0)
    {
        print_document(document);
    }
    else
    {
        printf("Incorrect password. View authorization rejected.\n");
    }
}

/**
 * @brief Print the contents of the specified document to the terminal.
 *
 * @param document The document to display.
 */
void print_document(Document *document)
{
    FILE *file = fopen(document->path, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open document\n");
        return;
    }

    printf("DOCUMENT ID: %s\n", document->id);
    printf("DOCUMENT NAME: %s\n", document->name);
    printf("DOCUMENT CATEGORY: %s\n\n", document->category);

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);

    printf("\n\n");
}

/**
 * @brief List available documents in the specified category.
 *
 * The following categories are available:
 *   public - Public documents
 *   secure - Secure documents
 *   logs - Log files
 *
 * A category must be specified. If no category is specified, or the category is invalid,
 * an error message will be displayed.
 *
 * The documents for each category are in directories with the same name as the category.
 *
 * The documents are listed in the following table format:
 *
 * | ID            | Name         |
 * |---------------|--------------|
 * | S-1           | Document1.md |
 * | S-2           | Document2.md |
 * | P-CASENUM-1   | Document3.md |
 * | P-CASENUM-2   | Document4.md |
 * | L-1           | system.log   |
 * | L-2           | system.log.2 |
 *
 * @param input The command entered by the user.
 */
void list_command(char *input)
{
    Document **docs = NULL;
    char *category = strtok(input, " ");
    if (category == NULL)
    {
        printf("Error: No category specified\n");
        return;
    }

    char *category_name = strtok(NULL, " ");
    if (category_name == NULL)
    {
        printf("Error: No category specified\n");
        return;
    }

    if (strcmp(category_name, "public") == 0)
    {
        docs = list_documents("./public");
    }
    else if (strcmp(category_name, "secure") == 0)
    {
        docs = list_documents("./secure");
    }
    else if (strcmp(category_name, "logs") == 0)
    {
        docs = list_documents("./logs");
    }
    else
    {
        printf("Error: Invalid category\n");
        return;
    }

    if (docs == NULL)
    {
        printf("Error listing documents\n");
        return;
    }

    printf("| %-14s | %-40s |\n", "ID", "Name");
    printf("|----------------|------------------------------------------|\n");
    for (int i = 0; docs[i] != NULL; i++)
    {
        printf("| %-14s | %-40s |\n", docs[i]->id, docs[i]->name);
    }

    for (int i = 0; docs[i] != NULL; i++)
    {
        free(docs[i]->id);
        free(docs[i]->name);
        free(docs[i]->path);
        free(docs[i]->category);
        free(docs[i]);
    }

    free(docs);
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
void start_message(void)
{
    int public_count = 0;
    int secure_count = 0;
    int logs_count = 0;
    DIR *dir;
    struct dirent *entry;

    printf("SecuRITE™ LEDAS™\n");
    printf("Law Enforcement Document Access System™\n");
    printf("v1.0.4 (Copyright © 2001)\n\n");

    printf("Authenticated User: %s\n\n", getenv("USER"));

    dir = opendir("./public");
    if (dir == NULL)
    {
        printf("Error opening public directory\n");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            public_count++;
        }
        else if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char subdir_path[1024];
                snprintf(subdir_path, sizeof(subdir_path), "./public/%s", entry->d_name);
                DIR *subdir = opendir(subdir_path);
                if (subdir != NULL)
                {
                    struct dirent *subentry;
                    while ((subentry = readdir(subdir)) != NULL)
                    {
                        if (subentry->d_type == DT_REG)
                        {
                            public_count++;
                        }
                    }
                    closedir(subdir);
                }
            }
        }
    }
    closedir(dir);

    dir = opendir("./secure");
    if (dir == NULL)
    {
        printf("Error opening secure directory\n");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            secure_count++;
        }
    }
    closedir(dir);

    dir = opendir("./logs");
    if (dir == NULL)
    {
        printf("Error opening logs directory\n");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            logs_count++;
        }
    }
    closedir(dir);

    printf("The following documents are available for browsing:\n");
    printf("Public documents: %d\n", public_count);
    printf("Secure documents: %d\n", secure_count);
    printf("Log files: %d\n", logs_count);
    printf("\nFor help, type 'help' and press Enter.\n");
}

/**
 * @brief List available documents in the specified directory.
 *
 * @param directory The directory to list documents from.
 *
 * @returns An array of Document pointers terminated by a NULL pointer.
 *
 * @note Document IDs are assigned as follows:
 *       - For documents directly within the specified directory, the ID is the capital first letter
 *         of the category name followed by a hyphen and then the index (starting at 1).
 *         Example: "S-1" for the first document in the secure directory.
 *       - For documents in subdirectories of the specified directory, the ID is the capital first letter
 *         of the category name followed by a hyphen, the name of the subdirectory, a hyphen, and then the
 *         index (starting at 1).
 *         Example: "P-subdir-1" for the first document in the "subdir" subdirectory of the public directory.
 */
Document **list_documents(char *directory)
{
    /* Extract the top-level category from the directory path.
       We remove any trailing '/' (if not the root "/") and then take the text after the last '/'. */
    size_t dir_len = strlen(directory);
    while (dir_len > 1 && directory[dir_len - 1] == '/')
        dir_len--;

    const char *cat_start = directory;
    for (size_t i = 0; i < dir_len; i++)
    {
        if (directory[i] == '/')
        {
            cat_start = directory + i + 1;
        }
    }
    /* If directory is "/" then cat_start remains "/" */

    /* Allocate an initial array for Document pointers */
    size_t capacity = 10;
    size_t count = 0;
    Document **docs = malloc(capacity * sizeof(Document *));
    if (!docs)
        return NULL;

    int top_index = 1; // Counter for files directly in the top-level directory

    /* Use scandir to read and sort the directory entries alphabetically */
    struct dirent **namelist;
    int n = scandir(directory, &namelist, NULL, alphasort);
    if (n < 0)
    {
        perror("Error");
        free(docs);
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        struct dirent *entry = namelist[i];

        /* Skip the current and parent directory entries */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            free(entry);
            continue;
        }

        if (entry->d_type == DT_REG)
        {
            /* Process a file directly within the specified directory */
            Document *doc = malloc(sizeof(Document));
            if (!doc)
            {
                free(entry);
                continue;
            }

            /* Set the document name */
            doc->name = strdup(entry->d_name);

            /* Construct the full file path: directory + "/" + filename */
            int path_len = snprintf(NULL, 0, "%s/%s", directory, entry->d_name);
            doc->path = malloc(path_len + 1);
            if (doc->path)
                sprintf(doc->path, "%s/%s", directory, entry->d_name);

            /* Set the category (a copy of the top-level category) */
            doc->category = strdup(cat_start);

            /* Build the document ID: e.g. "S-1" if top-level category starts with 's' */
            char id_buffer[256];
            snprintf(id_buffer, sizeof(id_buffer), "%c-%d", toupper(cat_start[0]), top_index);
            doc->id = strdup(id_buffer);
            top_index++;

            /* Expand the docs array if needed */
            if (count == capacity)
            {
                capacity *= 2;
                docs = realloc(docs, capacity * sizeof(Document *));
            }
            docs[count++] = doc;
        }
        else if (entry->d_type == DT_DIR)
        {
            /* Process subdirectories (skip "." and ".." already done) */
            char subdir_path[PATH_MAX];
            snprintf(subdir_path, sizeof(subdir_path), "%s/%s", directory, entry->d_name);

            struct dirent **sub_namelist;
            int m = scandir(subdir_path, &sub_namelist, NULL, alphasort);
            if (m < 0)
            {
                perror("scandir on subdirectory failed");
                free(entry);
                continue;
            }

            int sub_index = 1; // Counter for files within this subdirectory
            for (int j = 0; j < m; j++)
            {
                struct dirent *subentry = sub_namelist[j];

                if (strcmp(subentry->d_name, ".") == 0 || strcmp(subentry->d_name, "..") == 0)
                {
                    free(subentry);
                    continue;
                }

                if (subentry->d_type == DT_REG)
                {
                    Document *doc = malloc(sizeof(Document));
                    if (!doc)
                    {
                        free(subentry);
                        continue;
                    }

                    /* Set the document name */
                    doc->name = strdup(subentry->d_name);

                    /* Construct the full file path: directory/subdirectory/filename */
                    int full_path_len = snprintf(NULL, 0, "%s/%s/%s", directory, entry->d_name, subentry->d_name);
                    doc->path = malloc(full_path_len + 1);
                    if (doc->path)
                        sprintf(doc->path, "%s/%s/%s", directory, entry->d_name, subentry->d_name);

                    /* Category remains the top-level category */
                    doc->category = strdup(cat_start);

                    /* Build the document ID: e.g. "P-subdir-1" if top-level category starts with 'p' */
                    char id_buffer[256];
                    snprintf(id_buffer, sizeof(id_buffer), "%c-%s-%d", toupper(cat_start[0]), entry->d_name, sub_index);
                    doc->id = strdup(id_buffer);
                    sub_index++;

                    if (count == capacity)
                    {
                        capacity *= 2;
                        docs = realloc(docs, capacity * sizeof(Document *));
                    }
                    docs[count++] = doc;
                }
                free(subentry);
            }
            free(sub_namelist);
        }
        free(entry);
    }
    free(namelist);

    /* Terminate the array with a NULL pointer */
    docs = realloc(docs, (count + 1) * sizeof(Document *));
    docs[count] = NULL;

    return docs;
}