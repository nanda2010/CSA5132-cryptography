from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes from cryptography.hazmat.primitives import padding 
from cryptography.hazmat.backends import default_backend 
import os 
def xor_bytes(byte_str1, byte_str2): 
 return bytes([b1 ^ b2 for b1, b2 in zip(byte_str1, byte_str2)]) 
def cbc_mac(key, message): 
 cipher = Cipher(algorithms.AES(key), modes.ECB(), backend=default_backend())  encryptor = cipher.encryptor() 
 padder = padding.PKCS7(algorithms.AES.block_size).padder() 
 padded_message = padder.update(message) + padder.finalize() 
 iv = os.urandom(algorithms.AES.block_size) 
 prev_block = iv 
 for i in range(0, len(padded_message), algorithms.AES.block_size): 
 block = padded_message[i:i+algorithms.AES.block_size] 
 xor_result = xor_bytes(block, prev_block) 
 prev_block = encryptor.update(xor_result) 
  
 return prev_block 
def main(): 
 key = os.urandom(32) # Use 32 bytes for a 256-bit key 
 message = b"Hello, this is a one-block message." 
 t = cbc_mac(key, message) 
 x_xor_t = xor_bytes(message, t) 
 two_block_message = message + x_xor_t 
 cbc_mac_for_two_block = cbc_mac(key, two_block_message) 
 print("Original T (MAC for one-block message):", t.hex()) 
 print("Calculated CBC MAC for two-block message:", cbc_mac_for_two_block.hex()) 
if _name_ == "_main_": 
 main() 
