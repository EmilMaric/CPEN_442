#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <openssl/sha.h>


#define SALT                    "CS"
#define HASH                    "0DF2939D499DCC46A693653DB281FDBB016B502B"

#define PLAINTEXT_LEN           6


static const char* char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=";


unsigned char hex_lookup(char c) {
    char        result;
    uint8_t     int_val;

    // Initialize locals
    int_val = (unsigned int) c;

    if (int_val >= 48 && int_val <= 57) {
        int_val -= 48;
    } 
    else if (int_val >= 65 && int_val <= 70) {
        int_val -= 55;
    }
    else {
        // character integer value must fall within one of the accepted ranges
        assert(0);
    }

    return (unsigned char) int_val;
}

unsigned char *hex_to_string(char *hex_string) {
    int                 i;
    int                 hash_len;
    unsigned char       *string;
    unsigned char       upper;
    unsigned char       lower;
    unsigned char       character;

    // Initialize locals
    hash_len = strlen(hex_string);
    string = (unsigned char*) malloc(sizeof(unsigned char) * 21);

    for (i = 0; i < hash_len; i += 2) {
        upper = hex_lookup(hex_string[i]);
        lower = hex_lookup(hex_string[i + 1]);
        character = (unsigned char) (((int) upper) << 4);
        character = (unsigned char) (character | (((int) lower) & 0x0F));
        string[i / 2] = character;
    }
    string[20] = '\0';

    return string;
}

int main(int argc, char* argv[]) {
    uint64_t        count;
    uint64_t        max_count;
    char            *plaintext;
    unsigned char   *hash_match;
    unsigned int    i;
    uint64_t        char_set_idx;
    unsigned int    char_set_len;
    unsigned char   input_val[PLAINTEXT_LEN + strlen(SALT) + 1];
    unsigned char   hash[SHA_DIGEST_LENGTH];
    
    // Initialize locals
    count = 0;
    char_set_len = strlen(char_set);
    max_count = pow(char_set_len, PLAINTEXT_LEN);
    strncpy((char*) input_val, SALT, strlen(SALT));
    plaintext = (char*) &input_val[2];
    plaintext[PLAINTEXT_LEN] = '\0';

    hash_match = hex_to_string(HASH);
    assert(strlen(HASH) == 40);
    assert(strlen(SALT) == 2);
    assert(strlen((char*) hash_match) == 20);
    printf("##############################\n");
    printf("# Hash (hex): %s\n", HASH);
    printf("# Salt: %s\n", SALT);
    printf("##############################\n");
    printf("\n");

    //while (count < max_count) {
    while (count < max_count) {
        // fill in the plaintext
        for (i = 0; i < PLAINTEXT_LEN; i++) {
            char_set_idx = (count / ((unsigned int) pow(char_set_len, PLAINTEXT_LEN - 1 - i))) % char_set_len;
            plaintext[i] = char_set[char_set_idx];
        }

        //printf("Plaintext: %s\n", input_val);
        SHA1(input_val, strlen((char*) input_val), hash);
        //printf("Hash: %s\n", hash);

        if (strncmp((char*) hash_match, (char *) hash, 20) == 0) {
            break;
        }

        if ((count % 100000000) == 0) {
            printf("Count: %llu\n", count);
            printf("Plaintext: %s\n", input_val);
            printf("\n");
        }

        count++;
    }

    if (count < max_count) {
        printf("Found plaintext: %s\n", input_val);
    } else {
        printf("Could not find any matches.\n");
        printf("\n");
    }

    free(hash_match);

    return 0;
}
