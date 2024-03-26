#include <bits/stdc++.h>
using namespace std;

// Function to decrypt a monoalphabetic
// substitution cipher using the letter
// frequency attack
void printString(string S, int N)
{

	// Stores final 5 possible deciphered
	// plaintext
	string plaintext[5];

	// Store the frequency of each letter in
	// cipher text
	int freq[26] = { 0 };

	// Stores the frequency of each letter
	// in cipher text in descending order
	int freqSorted[26];

	// Store which alphabet is used already
	int Used[26] = { 0 };

	// Traverse the string S
	for (int i = 0; i < N; i++) {
		if (S[i] != ' ') {
			freq[S[i] - 'A']++;
		}
	}

	// Copy the frequency array
	for (int i = 0; i < 26; i++) {
		freqSorted[i] = freq[i];
	}

	// Stores the string formed from concatenating
	// the english letters in the decreasing frequency
	// in the english language
	string T = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

	// Sort the array in descending order
	sort(freqSorted, freqSorted + 26, greater<int>());

	// Iterate over the range [0, 5]
	for (int i = 0; i < 5; i++) {

		int ch = -1;

		// Iterate over the range [0, 26]
		for (int j = 0; j < 26; j++) {

			if (freqSorted[i] == freq[j] && Used[j] == 0) {
				Used[j] = 1;
				ch = j;
				break;
			}
		}
		if (ch == -1)
			break;

		// Store the numerical equivalent of letter at
		// ith index of array letter_frequency
		int x = T[i] - 'A';

		// Calculate the probable shift used
		// in monoalphabetic cipher
		x = x - ch;

		// Temporary string to generate one
		// plaintext at a time
		string curr = "";

		// Generate the probable ith plaintext
		// string using the shift calculated above
		for (int k = 0; k < N; k++) {

			// Insert whitespaces as it is
			if (S[k] == ' ') {
				curr += ' ';
				continue;
			}

			// Shift the kth letter of the
			// cipher by x
			int y = S[k] - 'A';
			y += x;

			if (y < 0)
				y += 26;
			if (y > 25)
				y -= 26;

			// Add the kth calculated/shifted
			// letter to temporary string
			curr += 'A' + y;
		}

		plaintext[i] = curr;
	}

	// Print the generated 5 possible plaintexts
	for (int i = 0; i < 5; i++) {
		cout << plaintext[i] << endl;
	}
}

// Driver Code
int main()
{
	// Given string
	string S = "B TJNQMF NFTTBHF";
	int N = S.length();

	// Function Call
	printString(S, N);

	return 0;
}
