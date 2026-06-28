#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
    // We expect 3 items: "./fileName" (argv[0]), "input.txt" (argv[1]), "encrypted.txt" (argv[2]), secret code/key (argv[3])
    if (argc != 4) {
        printf("Error: Missing parameters.\n");
        printf("Usage: %s <source_file> <destination_file> your_secret_passphrase\n", argv[0]);
        return 1; 
    }

    char *password = argv[3];
    int len = strlen(password);
    int index = 0;

    FILE *source = fopen(argv[1], "rb");
    FILE *destination = fopen(argv[2], "wb");

    if (source == NULL) {
        printf("Error: Could not open source file '%s'\n", argv[1]);
        return 1;
    }
    if (destination == NULL) {
        printf("Error: Could not create destination file '%s'\n", argv[2]);
        fclose(source); // Clean up the opened source stream before crashing out
        return 1;
    }

    int ch;
    /*
    EOF (End of File) - a macro constant (usually -1), if end of file is reach,
    meaning no char left, the fgetc() spits out -1 to signal the end.
    - fgetc() : "File Get Character" to pull one single byte out of file streamline
    or the fopen() 
    */
    while((ch = fgetc(source)) != EOF) {
        int byte_prc = ch ^password[index];
        fputc(byte_prc, destination);

        index = (index + 1) % len;
        /*
        Wrap-aroud logic

        so we have key_index = (key_index + 1) % key_len; since if password is 
        "gHscjk" and there are more characters in the input txt, it goes back to
        index 0 until txt file meets EOF
        */
    }
    
    fclose(source);
    fclose(destination);

    printf("Encryption/Decryption finished. File in %s\n", argv[2]);
    return 0;

    /*
    This code is used both for encrypting and decripting.
    if you put a normal file in argv[1], the destination argv[2] will be the encrypted file
    Otherwise, the destination will be the decrypted file.

    Note that the same password should be used encrypting/decrypting the SAME file
    */
}