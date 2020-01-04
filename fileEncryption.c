#include <stdio.h>
#include <stdlib.h>

#define BINFILENAME "results.bin"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Missing 1 or 2 arguments\n");
        return 0;
    }
    const char key = *(argv[1]);
    const char* filename = argv[2];
    int        rc  = 0;

    FILE *fd = fopen(filename, "r");
    // Error checking: Check if file exists or not
    if (!fd) {
        printf("ERROR: %s does not exist\n", filename);
        return -1;
    }
    // If the file does exist, continue encrypting
    // The program calculates the size of the file
    fseek(fd, 0, SEEK_END);
    unsigned long fsize = ftell(fd);
    printf("fsize = %lu\n", fsize);
    fseek(fd, 0, SEEK_SET);

    // Read the data
    char *encryption = (char *) malloc(fsize);
    char *encryptionStart = encryption;
    if (encryption == NULL) {
        printf("ERROR: Cannot malloc encryption\n");
        fclose(fd);
        return -2;
    }
    while (1) {
        // Read one character using fgetc
        char readChar = fgetc(fd);
        if (readChar == EOF) {
            break;
        }
        // Encrypt character
        char encryptedChar = readChar ^ key;
        *encryption++ = encryptedChar;
        // Decrypt character
        char decryptedChar = encryptedChar ^ key;
        // Compare with original
        if (decryptedChar != readChar) {
            printf("Error: Encryption does not work, readChar = 0x%02x, encryptedChar = 0x%02x, decryptedChar = 0x%02x", readChar, encryptedChar, decryptedChar);
            break;
        }
    } // while (1) {

    FILE *binFileDescriptor = fopen(BINFILENAME, "w");
    if (!binFileDescriptor) {
        printf("ERROR: Cannot open file %s\n", BINFILENAME);
        rc = -3;
    }
    else {
        fwrite(encryptionStart, fsize, 1, binFileDescriptor);
    }

    fclose(binFileDescriptor);
    free(encryptionStart);
    fclose(fd);

    return rc;
}