#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("text.txt", "rb+");  // Open in read/write binary mode
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);  // Go back to start of file

    unsigned char byte;
    // Loop through each character in the file
    for (long i = 0; i < file_size; i++) {
        // Read one byte
        fread(&byte, sizeof(unsigned char), 1, file);
        printf("Position %ld - Original Byte: %02X\n", i, byte);

        // Modify the byte (your original transformations)
        byte ^= 0xFF;  // XOR with 0xFF (inverts all bits)
        byte ^= 0xAE;  // XOR with 0xAE

        // Move back one position to write
        fseek(file, -1, SEEK_CUR);
        // Write the modified byte
        fwrite(&byte, sizeof(unsigned char), 1, file);
        // This is so that there is no error on the current position for the next for loop
        fseek(file, 0, SEEK_CUR);
    }

    fclose(file);
    printf("All bytes modified successfully!\n");

    return 0;
}
