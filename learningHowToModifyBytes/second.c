#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
    FILE *file = fopen("text.txt", "rb+");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 5, SEEK_SET);

    unsigned char byte;
    fread(&byte, sizeof(unsigned char), 1, file);
    printf("Original Byte: %02X\n", byte);

    byte ^= 0xFF;
    // generate a random byte to invert bits of the variable byte
    int currentTime = time(NULL);
    byte ^= currentTime;
    printf("Byte modified: %02X\n", byte);

    fseek(file, -1, SEEK_CUR);
    fwrite(&byte, sizeof(unsigned char), 1, file);

    fclose(file);
    printf("Byte modified successfully!\n");

    return 0;


}
