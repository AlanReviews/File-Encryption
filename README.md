# File-Encryption
Disclaimer: This program is not to be used for any real encryption and protection of files. The encryption performed is a byte-for-byte XOR using the same byte (the key is a single byte long). This scrambling is trivial to crack. It can possibly be seen as a simplified example of a Caesar cipher

This is a simple file encryption program I made with C on Linux. It is very easy to port it to Windows and Mac. I tested the program using Ubuntu 18.04. 


Steps
1. Compile the fileEncryption.c by calling gcc -o fileEncryption fileEncryption.c
2. Compile the fileDecryption.c by calling gcc -o fileDecryption fileDecryption.c
3. Run fileEncryption by calling ./fileEncryption [key] [filename]
4. Run fileDecryption by calling ./fileDecryption [key] [filename]
5. Compare the original and the decrypted by calling diff [original_file] results.txt
