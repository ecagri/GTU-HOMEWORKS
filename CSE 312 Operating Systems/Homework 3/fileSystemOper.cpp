#include "lib.h"

void dir(char*, char*, DirectoryEntry[]);

void mkdir(char*, char*, DirectoryEntry[]);

void rmdir(char*, char*, SuperBlock, DirectoryEntry[], int[], int[]);

void write(char*, char*, char*, SuperBlock, DirectoryEntry[], int[], int[]);

void del(char*, char*, SuperBlock, DirectoryEntry[], int[], int[]);

void read(char*, char*, char*, SuperBlock, DirectoryEntry[], int[]);

void dumpe2fs(SuperBlock, int[], int[], DirectoryEntry[]);

int isParent(char*, char*, DirectoryEntry[]);

int isExist(char **, int, DirectoryEntry[]);

int entryType(char*, char*, DirectoryEntry[]);

char** splitPath(char*, int*);

int directoryEntriesChanged = 0, fatTableChanged = 0, freeTableChanged = 0;

char * fileSystem;

int main(int argc, char * argv[]){
    if(argc < 3){
        printf("Insufficient number of elements...\n");
        exit(-1);
    }

    fileSystem = argv[1];

    char * operation = argv[2];

    char ** paths = &argv[3];

    FILE * file = fopen(fileSystem, "rb");
    if(file == NULL){
        perror("fopen");
        exit(-1);
    }
 
    SuperBlock superBlock;

    fread(&superBlock, sizeof(SuperBlock), 1, file);

    int free_table[superBlock.number_of_blocks];

    fread(&free_table, sizeof(int), superBlock.number_of_blocks, file);
    
    int fat_table[superBlock.number_of_blocks];

    fread(&fat_table, sizeof(int), superBlock.number_of_blocks, file);

    fseek(file, sizeof(SuperBlock) + (superBlock.fat_blocks + superBlock.free_blocks) * superBlock.block_size, SEEK_SET);

    DirectoryEntry directoryEntries[MAXNUMBEROFFILE];

    fread(directoryEntries, sizeof(DirectoryEntry), MAXNUMBEROFFILE, file);
    
    fclose(file);
    
    int number_of_elements = 2;

    char ** splittedPath;
    if(argc > 3)
        splittedPath = splitPath(paths[0], &number_of_elements);

    if(strncmp(operation, "dir", 3) == 0){
        if(!isExist(splittedPath, number_of_elements - 1, directoryEntries)){
            return -1;
        }
        dir(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], directoryEntries);
    }else if(strncmp(operation, "mkdir", 5) == 0){
        if(number_of_elements < 1){
            printf("INSUFFICENT PATH!\n");
            return -1;
        }
        if(!isExist(splittedPath, number_of_elements - 2, directoryEntries)){
            return -1;
        }
        mkdir(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], directoryEntries);
    }else if(strcmp(operation, "rmdir") == 0){
        if(!isExist(splittedPath, number_of_elements - 1, directoryEntries)){
            return -1;
        }
        rmdir(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], superBlock, directoryEntries, fat_table, free_table);
    }else if(strcmp(operation, "write") == 0){
        if(!isExist(splittedPath, number_of_elements - 3, directoryEntries)){
            return -1;
        }
        write(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[1], superBlock, directoryEntries, fat_table, free_table);
    }else if(strcmp(operation, "del") == 0){
        if(!isExist(splittedPath, number_of_elements - 1, directoryEntries)){
            return -1;
        }
        del(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], superBlock, directoryEntries, fat_table, free_table);
    }else if(strcmp(operation, "read") == 0){
        if(!isExist(splittedPath, number_of_elements - 1, directoryEntries)){
            return -1;
        }
        read(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[1], superBlock, directoryEntries, fat_table);
    }else if(strcmp(operation, "dumpe2fs") == 0){
        dumpe2fs(superBlock, free_table, fat_table, directoryEntries);
    }else{
        printf("\"%s\": NOT A VALID COMMAND", operation);
    }
    
    file = fopen(fileSystem, "rb+");
    if(file == NULL){
        perror("fopen");
        exit(-1);
    }
    if(directoryEntriesChanged == 1){

        rewind(file);

        fseek(file, sizeof(SuperBlock) + (superBlock.fat_blocks + superBlock.free_blocks) * superBlock.block_size, SEEK_SET);

        fwrite(directoryEntries, sizeof(DirectoryEntry), MAXNUMBEROFFILE, file);

    }
    if(fatTableChanged == 1){
        rewind(file);

        fseek(file, sizeof(SuperBlock) + (superBlock.block_size * superBlock.free_blocks), SEEK_SET);

        for(int i = 0; i < superBlock.number_of_blocks; i++){
            fwrite(&fat_table[i], sizeof(int), 1, file);
        }
    }
    if(freeTableChanged == 1){
        rewind(file);

        fseek(file, sizeof(SuperBlock), SEEK_SET);

        for(int i = 0; i < superBlock.number_of_blocks; i++){
            fwrite(&free_table[i], sizeof(int), 1, file);
        }
    }

    fclose(file);

    return 0;
}

void dir(char * parent, char * child, DirectoryEntry directoryEntries[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 0){ // IT IS A FILE
        printf("%s", child);
    }else{
        int number_of_files = 0;
        for(int i = 0; i < MAXNUMBEROFFILE; i++){
            if(strcmp(directoryEntries[i].parent, child) == 0){
                printf("%s\t", directoryEntries[i].filename);
                number_of_files++;
            }
        }
        if(number_of_files > 0)
            printf("\n");
    }
}

void mkdir(char * parent, char * child, DirectoryEntry directoryEntries[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == -1){
        for(int i = 0; i < MAXNUMBEROFFILE; i++){
            if(directoryEntries[i].exist != 999){
                strcpy(directoryEntries[i].filename, child);
                strcpy(directoryEntries[i].parent, parent);
                time(&directoryEntries[i].last_modification);
                directoryEntries[i].directory = 1;
                directoryEntries[i].size = 0;
                directoryEntriesChanged = 1;
                directoryEntries[i].exist = 999;
                return;
            }
        }
    }else if(fileType == 0){ // THERE IS A FILE ALREADY WITH GIVEN NAME //

    }else if(fileType == 1){
        printf("CANNOT CREATE DIRECTORY \"%s\": IT EXISTS!\n", child);
    }
}

void rmdir(char * parent, char * child, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 0){ // IT IS A FILE
        printf("FAILED TO REMOVE \"%s\": NOT A DIRECTORY!\n", child);
    }else if(fileType == -1){
        printf("FAILED TO REMOVE \"%s\": NO SUCH FILE OR DIRECTORY!\n", child);
    }else{
        for(int i = 0; i < MAXNUMBEROFFILE; i++){
            if(strcmp(directoryEntries[i].parent, child) == 0){
                if(directoryEntries[i].directory == 1){
                    rmdir(child, directoryEntries[i].filename, superBlock, directoryEntries, fat_table, free_table);
                }else{
                    del(child, directoryEntries[i].filename, superBlock, directoryEntries, fat_table, free_table);
                } 
            }
            if(strcmp(directoryEntries[i].filename, child) == 0){
                strcpy(directoryEntries[i].filename, "");
                strcpy(directoryEntries[i].parent, "");
                directoryEntries[i].last_modification = 0;
                directoryEntries[i].directory = 0;
                directoryEntries[i].size = 0;
                directoryEntriesChanged = 1;
                directoryEntries[i].exist = 0;
                break;
            }
        }
        freeTableChanged = 1;
        fatTableChanged = 1;
    }
}

void write(char * parent, char * child, char * filename, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 1){
        printf("\"%s\": IS A DIRECTORY!\n", child);
    }else{
        if(fileType == 0){
            del(parent, child, superBlock, directoryEntries, fat_table, free_table);
        }

        FILE * file = fopen(filename, "rb");
        if(file == NULL){
            perror("fopen");
            exit(-1);
        }

        fseek(file, 0, SEEK_END);

        int size = ftell(file);

        rewind(file);

        int file_blocks = (size / superBlock.block_size) + 1;

        char ** fileArray = (char**) malloc(file_blocks * sizeof(char*));

        for(int i = 0; i < file_blocks; i++){
            fileArray[i] = (char*) malloc(superBlock.block_size * sizeof(char));
            fread(fileArray[i], sizeof(char), superBlock.block_size, file);
        }

        int counter = 0;

        FILE * fptr = fopen(fileSystem, "rb+");
        if(fptr == NULL){
            perror("fopen");
            exit(-1);
        }
        int next = -1;
        for(int i = 0; i < superBlock.number_of_blocks && counter < file_blocks; i++){
            if(free_table[i] == 1){ // FREE BLOCK IS FOUND. //
                fat_table[i] = next;
                free_table[i] = 0;
                next = i;
                fseek(fptr, sizeof(SuperBlock) + i * superBlock.block_size, SEEK_SET);
                fwrite(fileArray[file_blocks - counter - 1], sizeof(char), superBlock.block_size, fptr);
                rewind(fptr);
                counter++;
            }
        }

        if(counter != file_blocks){
            printf("SOME PARTS OF THE FILE IS NOT WRITTEN TO \"%s\": MEMORY IS FULL!\n", child);
        }

        fclose(file);
        fclose(fptr);

        for(int i = 0; i < MAXNUMBEROFFILE; i++){
            if(directoryEntries[i].exist != 999){
                strcpy(directoryEntries[i].filename, child);
                strcpy(directoryEntries[i].parent, parent);
                time(&directoryEntries[i].last_modification);
                directoryEntries[i].directory = 0;
                directoryEntries[i].size = size;
                directoryEntries[i].first_block = next;
                directoryEntries[i].exist = 999;
                break;
                // UPDATE PARENTS SIZE //
            }
        }
        
        freeTableChanged = 1;
        fatTableChanged = 1;
        directoryEntriesChanged = 1;

    }
}

void del(char * parent, char * child, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 1){
        printf("\"%s\": IS A DIRECTORY!\n", child);
    }else if(fileType == -1){
        printf("\"%s\": NO SUCH FILE OR DIR!\n", child);   
    }else{
        for(int i = 0; i < MAXNUMBEROFFILE; i++){
            if(strcmp(directoryEntries[i].filename, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
                int current = directoryEntries[i].first_block; 
                int next;
                do{
                    next = fat_table[current]; 
                    free_table[current] = 1;
                    fat_table[current] = -1;
                    current = next; 

                }while(current != -1);
                strcpy(directoryEntries[i].filename, "");
                strcpy(directoryEntries[i].parent, "");
                directoryEntries[i].last_modification = 0;
                directoryEntries[i].directory = 0;
                directoryEntries[i].size = 0;
                directoryEntries[i].exist = 0;
                break;
            }
        }
        freeTableChanged = 1;
        fatTableChanged = 1;
        directoryEntriesChanged = 1;
    }
}

void read(char * parent, char * child, char * filename, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 1){
        printf("\"%s\": IS A DIRECTORY!\n", child);
    }else if(fileType == -1){
        printf("\"%s\": NO SUCH FILE OR DIR!\n", child);   
    }else{
        FILE * file = fopen(filename, "w");
        FILE * fptr = fopen(fileSystem, "rb+");
        for(int i = 0; i < MAXNUMBEROFFILE; i++){
            if(strcmp(directoryEntries[i].filename, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
                int start = directoryEntries[i].first_block;

                while(start != -1){
                    char buffer[superBlock.block_size];

                    fseek(fptr, sizeof(SuperBlock) + start * superBlock.block_size, SEEK_SET);

                    fread(buffer, sizeof(char), superBlock.block_size, fptr);

                    rewind(fptr);

                    fwrite(buffer, sizeof(char), strlen(buffer), file);

                    memset(buffer, 0, sizeof(buffer));

                    start = fat_table[start];
                }
                break;
            }
        }
        fclose(file);
        fclose(fptr);
    }
}

void dumpe2fs(SuperBlock superBlock, int free_table[], int fat_table[], DirectoryEntry directoryEntries[]){
    printf("BLOCK SIZE: %d\nNUMBER OF BLOCKS: %d\n", superBlock.block_size, superBlock.number_of_blocks);
    int free_blocks_counter = 0, file_counter = 0, directory_counter = 0;
    for(int i = 0; i < superBlock.number_of_blocks; i++){
        free_blocks_counter += free_table[i];
    }
    printf("FREE BLOCKS NUMBER: %d\n", free_blocks_counter);

    for(int i = 0; i < MAXNUMBEROFFILE; i++){
        if(directoryEntries[i].exist == 999){
            if(directoryEntries[i].directory == 1){
                directory_counter++;
            }else{
                file_counter++;
            }
        }
    }
    printf("NUMBER OF FILES: %d\n", file_counter);
    printf("NUMBER OF DIRECTORIES: %d\n", directory_counter);

    for(int i = 0; i < MAXNUMBEROFFILE; i++){
        if(directoryEntries[i].exist == 999 && directoryEntries[i].directory == 0){
            printf("OCCUPIED BLOCKS FOR %s: ", directoryEntries[i].filename);
            int start = directoryEntries[i].first_block;
            while(start != -1){
                printf("%d ", start);
                start = fat_table[start];
            }
            printf("\n");
        }
    }



}


char** splitPath(char * path, int * number_of_elements){
    char ** splittedPath = (char**) malloc(100 * sizeof(char*));

    splittedPath[0] = strdup("NOPARENT");

    splittedPath[1] = strdup("/");

    char * token = strtok(path, "/");

    for(int i = 2; i < 100 && token != NULL; i++){
        splittedPath[i] = token;
        token = strtok(NULL, "/");
        (*number_of_elements)++;
    }
    return splittedPath;
}

int entryType(char * parent, char * child, DirectoryEntry directoryEntries[]){
    for(int i = 0; i < MAXNUMBEROFFILE; i++){
        if(strcmp(directoryEntries[i].filename, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
            return directoryEntries[i].directory;
        }
    }
    return -1;
}

int isParent(char * parent, char * child, DirectoryEntry directoryEntries[]){
    for(int i = 0; i < MAXNUMBEROFFILE; i++){
        if(strcmp(directoryEntries[i].filename, child) == 0){
            if(strcmp(directoryEntries[i].parent, parent) == 0){
                return 1;
            }
        }
    }
    return 0;
}

int isExist(char ** splittedPath, int until, DirectoryEntry directoryEntries[]){
    for(int i = 0; i < until; i++){
        if(!isParent(splittedPath[i], splittedPath[i + 1], directoryEntries)){
            printf("NO SUCH FILE OR DIR!\n");
            return 0;
        }
    }
    return 1;
}