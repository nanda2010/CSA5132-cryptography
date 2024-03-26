#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// English letter frequency
const float english_frequency[26] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202,  // A-G
    0.0609, 0.0697, 0.0015, 0.0077, 0.0402, 0.0241, 0.0675,  // H-N
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276,  // O-U
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007                   // V-Z
};

// Function to calculate the frequency of each letter in the ciphertext
void calculate_frequency(const char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            frequency[tolower(ciphertext[i]) - 'a']++;
        }
    }
}

// Function to calculate the chi-square value for a given key
float calculate_chi_square(const int *frequency, const float *expected_frequency) {
    float chi_square = 0;
    for (int i = 0; i < 26; i++) {
        chi_square += ((frequency[i] - expected_frequency[i]) * (frequency[i] - expected_frequency[i])) / expected_frequency[i];
    }
    return chi_square;
}

// Function to decrypt the ciphertext using a given key
void decrypt(const char *ciphertext, char *plaintext, const int *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                plaintext[i] = toupper('a' + key[ciphertext[i] - 'A']);
            } else {
                plaintext[i] = 'a' + key[ciphertext[i] - 'a'];
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}

// Function to perform letter frequency attack
void frequency_attack(const char *ciphertext, int num_results) {
    int frequency[26] = {0};
    calculate_frequency(ciphertext, frequency);

    // Calculate the chi-square value for each possible key
    float chi_square_values[26] = {0};
    for (int i = 0; i < 26; i++) {
        int shifted_frequency[26] = {0};
        for (int j = 0; j < 26; j++) {
            shifted_frequency[j] = frequency[(j + i) % 26];
        }
        chi_square_values[i] = calculate_chi_square(shifted_frequency, english_frequency);
    }

    // Sort the keys based on chi-square values
    int sorted_keys[26];
    for (int i = 0; i < 26; i++) {
        sorted_keys[i] = i;
    }
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (chi_square_values[sorted_keys[i]] > chi_square_values[sorted_keys[j]]) {
                int temp = sorted_keys[i];
                sorted_keys[i] = sorted_keys[j];
                sorted_keys[j] = temp;
            }
        }
    }

    // Display possible plaintexts
    printf("Top %d possible plaintexts:\n", num_results);
    for (int i = 0; i < num_results; i++) {
        char plaintext[strlen(ciphertext) + 1];
        decrypt(ciphertext, plaintext, sorted_keys[i]);
        printf("%d. %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[1000];
    int num_results;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &num_results);

    frequency_attack(ciphertext, num_results);

    return 0;
}
