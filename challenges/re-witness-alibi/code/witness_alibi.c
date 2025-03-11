#include <stdio.h>

__attribute__((section(".rodata"))) volatile const char *strings[] = {
    "kn1f3",        // 0
    "p01s0n",       // 1
    "stud3y",       // 2
    "l1br4ry",      // 3
    "m0t1v3",       // 4
    "susp3ct",      // 5
    "4l1b1",        // 6
    "w1tn3ss",      // 7
    "butl3r",       // 8
    "g4rd3n3r",     // 9
    "m4ns10n",      // 10
    "3st4t3",       // 11
    "1nh3r1t4nc3",  // 12
    "w1ll",         // 13
    "d3t3ct1v3",    // 14
    "1nsp3ct0r",    // 15
    "clU3",         // 16
    "3v1d3nc3",     // 17
    "f00tpr1nts",   // 18
    "bl00dst41n",   // 19
    "v1ct1m",       // 20
    "w34p0n",       // 21
    "s3cr3t",       // 22
    "p4ss4g3",      // 23
    "l3tt3r",       // 24
    "h4x0r",        // 25
    "r3v3rs3",      // 26
    "d3bug",        // 27
    "3xpl01t",      // 28
    "pwn3d",        // 29
    "n0t",          // 30
    "crazy",        // 31
    "k1ll3rs",      // 32
};

__attribute__((section(".rodata"))) volatile const char *salts[] = {
    "a1b2c3d4", //0
    "9f86d081", //1
    "7e5a4d9c", //2
    "2c3b4a5f", //3
    "6g7h8i9j", //4
    "1a3z5q7w", //5
    "e4r5t6y7", //6
    "8u7i6o5p", //7
    "f1a2s3d4", //8
    "q9w8e7r6", //9
    "z1x2c3v4", //10
    "p0o9i8u7", //11
    "t6r5e4w3", //12
    "4d5e6f7a", //13
};

__attribute__((section(".data"))) volatile int decoy_idx[] = {30, 31, 32};
__attribute__((section(".data"))) volatile int decoy_salt_idx = 0;

// Super secret password
__attribute__((section(".data"))) volatile int real_idx[] = {29, 5, 6};
__attribute__((section(".data"))) volatile int real_salt_idx = 5;

int main() {
    printf("cssactf{%s_4_%s_%s_%s}\n", strings[decoy_idx[0]],strings[decoy_idx[1]],strings[decoy_idx[2]],salts[decoy_salt_idx]);

    return 0;
}
