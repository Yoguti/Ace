#ifndef ENCRYPT_H
#define ENCRYPT_H

char* caesar_encrypt(const char* path);
char* vigenere_encrypt(const char* input, const char* key);
char* rsa_encrypt(const char* input, const char* public_key);
char* playfair_encrypt(const char* input, const char* key);

#endif // ENCRYPT_H
