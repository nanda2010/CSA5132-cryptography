#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16

// Function prototypes
void encrypt_ecb(const unsigned char *plaintext, int plaintext_len, unsigned char *key);
void encrypt_cbc(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv);
void encrypt_cfb(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv);

int main() {
    unsigned char key[] = "0123456789abcdef"; // 128-bit key
    unsigned char iv[] = "abcdefghijklmnop"; // 128-bit IV
    unsigned char plaintext[256];
    int plaintext_len;

    printf("Enter plaintext (multiple of 16 characters): ");
    scanf("%s", plaintext);
    plaintext_len = strlen(plaintext);

    // Padding the plaintext if necessary
    int padding_len = BLOCK_SIZE - (plaintext_len % BLOCK_SIZE);
    if (padding_len != BLOCK_SIZE) {
        for (int i = 0; i < padding_len - 1; ++i) {
            plaintext[plaintext_len + i] = '\0';
        }
        plaintext[plaintext_len + padding_len - 1] = 1; // Adding 1 followed by zero padding
        plaintext_len += padding_len;
    }

    // Encrypt using ECB mode
    encrypt_ecb(plaintext, plaintext_len, key);

    // Encrypt using CBC mode
    encrypt_cbc(plaintext, plaintext_len, key, iv);

    // Encrypt using CFB mode
    encrypt_cfb(plaintext, plaintext_len, key, iv);

    return 0;
}

void encrypt_ecb(const unsigned char *plaintext, int plaintext_len, unsigned char *key) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);

    unsigned char ciphertext[256];
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &enc_key);
    }

    printf("ECB Mode: ");
    for (int i = 0; i < plaintext_len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
}

void encrypt_cbc(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);

    unsigned char ciphertext[256];
    unsigned char xor_block[BLOCK_SIZE];
    memcpy(xor_block, iv, BLOCK_SIZE); // Set IV as the first XOR block

    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            xor_block[j] ^= plaintext[i + j];
        }
        AES_encrypt(xor_block, ciphertext + i, &enc_key);
        memcpy(xor_block, ciphertext + i, BLOCK_SIZE); // Set the previous ciphertext block as the next XOR block
    }

    printf("CBC Mode: ");
    for (int i = 0; i < plaintext_len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
}

void encrypt_cfb(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);

    unsigned char ciphertext[256];
    unsigned char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE); // Set IV as the first feedback block

    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        AES_encrypt(feedback, feedback, &enc_key); // Generate keystream
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            ciphertext[i + j] = plaintext[i + j] ^ feedback[j]; // XOR with plaintext to produce ciphertext
        }
        memcpy(feedback, ciphertext + i, BLOCK_SIZE); // Set previous ciphertext block as the next feedback block
    }

    printf("CFB Mode: ");
    for (int i = 0; i < plaintext_len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
}
