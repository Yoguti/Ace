#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/definitions.h"
#include <libgen.h>
#include <linux/limits.h> 
#include <unistd.h>


/* int caesar_encrypt(const char* path) {
    FILE *file = fopen(path, "rb+");
    if (file == NULL) {
        perror("Unable to open file");
        return STATUS_ERROR;
    }
    fclose(file);
    return STATUS_SUCCESS;
} */

int caesar_encrypt(void) {
    char program_path[PATH_MAX];
    char *dir_path;
    
    // Get the path of the executable
    ssize_t len = readlink("/proc/self/exe", program_path, sizeof(program_path) - 1);
    if (len == -1) {
        perror("Error resolving program path");
        return STATUS_ERROR;
    }
    program_path[len] = '\0';
    
    dir_path = dirname(program_path);
    
    char file_path[PATH_MAX];
    snprintf(file_path, sizeof(file_path), "%s/../info/decrypt.info", dir_path);
    
    FILE *file = fopen(file_path, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return STATUS_ERROR;
    }
    int ch; 
    int pos = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 'A' && ch <= 'Z') {         
            ch = ((ch - 'A' + 3) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {  
            ch = ((ch - 'a' + 3) % 26) + 'a';
        }
        fseek(file, pos, SEEK_SET);
        fputc(ch, file);
        pos++; 
    }

    fclose(file);
    return STATUS_SUCCESS;
}

