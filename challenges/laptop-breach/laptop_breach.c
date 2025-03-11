#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void state_0() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 161, 248, 181, 174, 255, 147, 173, 147, 190, 255, 255, 160, 147, 170, 160, 173, 171, 177};
    for (int i = 0; i < 26; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_1() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 168, 169, 170, 165, 162, 253, 184, 169, 160, 181, 147, 162, 252, 184, 147, 173, 147, 170, 160, 173, 171, 177};
    for (int i = 0; i < 30; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_2() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 170, 160, 173, 171, 147, 248, 147, 169, 168, 187, 237, 162, 177};
    for (int i = 0; i < 21; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_3() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 162, 252, 184, 147, 185, 190, 147, 173, 186, 171, 147, 161, 185, 190, 168, 255, 190, 177};
    for (int i = 0; i < 26; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_4() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 190, 255, 168, 147, 164, 255, 190, 190, 253, 162, 171, 177};
    for (int i = 0; i < 20; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_5() {
     unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 174, 185, 184, 160, 255, 190, 147, 168, 253, 168, 147, 253, 184, 177};
    for (int i = 0; i < 22; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_6() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 248, 175, 175, 169, 249, 249, 147, 171, 190, 248, 162, 184, 255, 168, 237, 177};
    for (int i = 0; i < 24; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_7() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 248, 160, 161, 252, 249, 251, 147, 132, 248, 168, 147, 253, 251, 177};
    for (int i = 0; i < 22; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_8() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 175, 160, 252, 249, 169, 147, 174, 185, 184, 147, 162, 252, 188, 177};
    for (int i = 0; i < 22; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void state_9() {
    unsigned char str[] = {175, 191, 191, 173, 175, 184, 170, 183, 170, 248, 165, 160, 185, 190, 255, 147, 254, 147, 164, 248, 180, 177};
    for (int i = 0; i < 22; i++) {
        putchar(str[i] ^ 0xcc);
    }
    printf("\n");
}

void (*states[])() = {
    state_0, state_1, state_2, state_3, state_4,
    state_5, state_6, state_7, state_8, state_9
};

void terminate() {
	printf("Access denied. Please enter the correct password.\n");
	exit(1);
}

int silly_check_1(char *word) {
	if (strlen(word) > 15 | strlen(word) < 5) {
		return 0;
	}
	return 1;
}

int silly_check_2(char *word) {
	int sum = 0;

	for (int i = 0; i < strlen(word); ++i) {
		if (isdigit(word[i])) {
			sum += word[i] - '0';
		}
	}

	return sum != 15;
}

int check_1(char *word) {
	if (strstr(word, "win") != NULL) {
		return 1;
	}

	return 0;
}


int dumb_function(char *word) {
	return strcmp(word, "flagpls78");
}

int calculate_bogus_checksum(char *word) {
    int checksum = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        checksum += (word[i] * (i + 1)) ^ 0x5A;
        checksum %= 256;
        checksum = (checksum << 3) | (checksum >> 5);
    }
    return checksum;
}

int another_check(char *word, int important_var) {
	int local_secret = 0x57;
	for (int i = 0; i < strlen(word); ++i) {
		local_secret &= important_var - 0xc;	
		local_secret *= isalnum(word[i]);
		local_secret &= important_var;
	}

	return (local_secret != 0);
}

int fetch_digit(char *word) {
	for(int i = 0; i < strlen(word); ++i) {
		if (isdigit(word[i])) {
			return word[i] - '0';
		}
	}

	return 8;
}

void check_flag(char *word) {
	if (!silly_check_1(word)) {
		terminate();
	}

	if (silly_check_2(word)) {
		terminate();
	}

	if (!check_1(word)) {
		terminate();
	}

	int important_var = calculate_bogus_checksum(word);
	
	if (another_check(word, important_var)) {
		terminate();
	}

	int other_important_var = fetch_digit(word);

	states[other_important_var]();
}


int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./laptop_breach <password>\n");
		exit(1);
	}

	check_flag(argv[1]);
	return 0;
}
