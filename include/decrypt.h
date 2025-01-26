#ifndef DECRYPT_H
#define DECRYPT_H

#include <stddef.h>

int caesar_decrypt(const char* input, int key);
int vigenere_decrypt(const char* input, const char* key);
int rsa_decrypt(const char* input, const char* private_key);
int playfair_decrypt(const char* input, const char* key);

#endif // DECRYPT_H
