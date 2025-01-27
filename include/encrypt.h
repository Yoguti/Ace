#ifndef ENCRYPT_H
#define ENCRYPT_H

int caesar_encrypt_file(const char* path);
int vigenere_encrypt_file(const char* path, const char* key);
int rsa_encrypt_file(const char* path, const char* public_key);
int playfair_encrypt_file(const char* path, const char* key);

int caesar_encrypt(void);
char* vigenere_encrypt(const char* input, const char* key);
char* rsa_encrypt(const char* input, const char* public_key);
char* playfair_encrypt(const char* input, const char* key);

#endif // ENCRYPT_H
