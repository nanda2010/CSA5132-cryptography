def decrypt_simple_substitution(ciphertext, key): 
 decryption = ""
 for char in ciphertext: 
 if char.isalpha(): 
 decrypted_char = key[char] 
 decryption += decrypted_char 
 else: 
 decryption += char 
 return decryption 
ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 " \  "(88)5*†;46(;88*96*?;8)‡(;485);5†2:‡(;4956*2(5—4)8¶8* " \  ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 " \  "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;" 
  
# Hints 
hints = { 
 '†': 'E', # E is the most frequent letter 
 '4': 'T', # T is one of the most common letters 
 '8': 'H', # H often follows T 
 '†': 'E', # E is often seen in pairs 
 '3': 'R', # R is common and could follow H 
 '1': 'A', # A is common and could follow T 
 ';': 'N', # N is common and could follow A 
 '6': 'I', # I is common and could follow A 
 '5': 'S', # S is common and could follow H 
 '0': 'O', # O is common and could follow T 
 '—': 'F', # F is common and could follow O 
 ':': 'U', # U is common and could follow Q 
 ']': 'L', # L could follow U 
 '(': 'W', # W is a possibility for second most common letter
 '(': 'W', # W is a possibility for second most common letter 
 ')': 'Y', # Y could follow W 
 '?': 'G', # G is a possibility for third most common letter 
} 
# Decrypt the message using the provided hints 
decryption_key = {k: v for k, v in hints.items() if k.isalpha()} 
decrypted_message = decrypt_simple_substitution(ciphertext, decryption_key) 
print("Decrypted Message:") 
print(decrypted_message) 
