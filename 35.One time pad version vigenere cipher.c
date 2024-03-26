#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *plaintext, char *key) {
    int i;
    int len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            // Encrypt uppercase letters
            plaintext[i] = ((plaintext[i] - 'A' + (key[i] - 'A')) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            // Encrypt lowercase letters
            plaintext[i] = ((plaintext[i] - 'a' + (key[i] - 'A')) % 26) + 'a';
        }
    }
}

int main() {
    char plaintext[256];
    char key[256];
    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    int i;
    int len = strlen(plaintext);
    int key_len = strlen(key);

    // Remove newline characters from inputs
    for (i = 0; i < len; i++) {
        if (plaintext[i] == '\n') {
            plaintext[i] = '\0';
            break;
        }
    }
    for (i = 0; i < key_len; i++) {
        if (key[i] == '\n') {
            key[i] = '\0';
            break;
        }
    }

    // Encrypt plaintext using one-time pad Vigenère cipher
    encrypt(plaintext, key);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
