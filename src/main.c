#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <unistd.h>
#include "../include/writep.h"

void print_usage(void)
{
    printf("\t -p : must be followed by the number of processes you wish to send to .info file\n");
    printf("\t -e : must be followed by an encryption (aka ceasar, vigenere...) comma (,) an absolute path to a file\n");
    printf("\t -d : must be followed by an decryption (aka ceasar, vigenere...) comma (,) an absolute path to a file\n");
    return;
}

int main(int argc, char *argv[])
{
    int c;
    int times = -1;
    char *encrypt = NULL;
    char *decrypt = NULL;

    while ((c = getopt(argc, argv, "p:d:e:")) != -1)
    {
        switch (c)
        {
        case 'e':
            encrypt = optarg;
            break;
        case 'd':
            decrypt = optarg;
            break;
        case 'p':
            times = atoi(optarg);
            break;
        case '?':
            print_usage();
            return -1;
        }
    }

    if (times != -1)
    {
        ProcessMonitor monitor;
        init_monitor(&monitor);

        if (update_processes(&monitor) > 0)
        {
            write_processes_to_file(&monitor, times);
        }
        return 0;
    }
    
    if (encrypt != NULL)
    {
        char *type = strtok(encrypt, ",");
        char *absolute_path = strtok(NULL, ",");
        // call to encrypt
        return 0;
    } else if (decrypt != NULL)
    {
        char *type = strtok(decrypt, ",");
        char *absolute_path = strtok(NULL, ",");
        // call to decrypt
        return 0;
    } else {
        print_usage();
        return -1;
    }
    

    return 0;
}