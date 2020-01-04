#include <stdio.h>
#include <stdlib.h>

#define FILENAME    "results.txt"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Missing 1 or 2 arguments\n");
        return 0;
    }
    const char key = *(argv[1]);
    const char* filename = argv[2];
    int        rc  = 0;

    FILE *binFileDescriptor = fopen(filename, "r");
    // Error checking: Check if file exists or not
    if (!binFileDescriptor) {
        printf("ERROR: %s does not exist\n", filename);
        return -1;
    }
    // If the file does exist, continue encrypting
    // The program calculates the size of the file
    fseek(binFileDescriptor, 0, SEEK_END);
    unsigned long fsize = ftell(binFileDescriptor);
    printf("fsize = %lu\n", fsize);
    fseek(binFileDescriptor, 0, SEEK_SET);

    // Read the data
    char *decryption = (char *) malloc(fsize);
    char *decryptionStart = decryption;
    if (decryption == NULL) {
        printf("ERROR: Cannot malloc decryption array\n");
        fclose(binFileDescriptor);
        return -2;
    }
    while (1) {
        // Read one character using fgetc
        char readChar = fgetc(binFileDescriptor);
        if (readChar == EOF) {
            break;
        }
        // Decrypt character
        *decryption++ = readChar ^ key;
    } // while (1) {

    FILE *fd = fopen(FILENAME, "w");
    if (!fd) {
        printf("ERROR: Cannot open file %s\n", FILENAME);
        rc = -3;
    }
    else {
        fwrite(decryptionStart, fsize, 1, fd);
    }

    fclose(fd);
    free(decryptionStart);
    fclose(binFileDescriptor);

    return rc;
}