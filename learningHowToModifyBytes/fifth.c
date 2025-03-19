// This program does the following
// opens text.txt to read and write in binary mode
// if failed to open the program stops
// gets the filesize so that each character can be iterated
// reads and prints each byte according to the position(i)
// inverts the bits in that byte making all 1's 0's and all 0's 1's
// it later randomizes that byte even more with a random number
// goes back one position because fread moved the position to the next character(11th position)
// writes the modified byte to that position
// and after that, fseek(file, 0, SEEK_CUR); makes sure that there is no error in finding the current position for the next iteration
// lastly, closes the file and prints success

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("text.txt", "rb+");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    unsigned char byte;
    int currentTime = time(NULL);

    for (long i = 0; i < fileSize; i++) {
        fread(&byte, sizeof(unsigned char), 1, file);

        byte ^= 0xFF;
        if ((i % 2) == 0) {
            byte ^= currentTime;
        }

        fseek(file, -1, SEEK_CUR);
        fwrite(&byte, sizeof(unsigned char), 1, file);
        fseek(file, 0, SEEK_CUR);
    }
    fclose(file);
    printf("Program executed");

    return 0;
}
