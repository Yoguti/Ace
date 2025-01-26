#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/definitions.h"

char* caesar_encrypt(const char* path) {
    FILE *file = fopen(path, "rb+");
    if (file == NULL) {
        perror("Unable to open file");
        return STATUS_ERROR;
    }

    

    fclose(file);
    return STATUS_SUCCESS;
}
