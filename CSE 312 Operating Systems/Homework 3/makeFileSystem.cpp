#include "lib.h"

int main(int argc, char * argv[]){

    if(argc < 3){
        printf("Insufficient number of elements...\n");
        exit(-1);
    }

    int block_size = 1024 * atoi(argv[1]); /* BLOCK SIZE IS CALCULATED. */

    int number_of_blocks = MAXSIZE / block_size; /* NUMBER OF BLOCKS IS CALCULATED. */

    int fat_blocks = ((number_of_blocks * sizeof(int)) + block_size - 1) / block_size; /* NUMBER OF FAT BLOCKS IS CALCULATED. */

    int directory_blocks = ((MAXNUMBEROFFILE * sizeof(DirectoryEntry)) + block_size - 1) / block_size; /* NUMBER OF DIRECTORY BLOCKS IS CALCULATED. */

    int free_blocks = ((number_of_blocks * sizeof(int)) + block_size - 1) / block_size; /* NUMBER OF FREE BLOCKS IS CALCULATED. */

    char * filename = argv[2];

    char rootName[128] = "/", rootParent[128] = "NOPARENT";

    int next = 0;

    FILE * file = fopen(filename, "wb");
    if(file == NULL){
        perror("fopen");
        exit(-1);
    }
    SuperBlock superBlock(block_size, number_of_blocks, free_blocks, fat_blocks, directory_blocks);

    DirectoryEntry rootDir(rootName, rootParent, 0, 0, 0, 1);

    fwrite(&superBlock, sizeof(SuperBlock), 1, file);

    int free_table[number_of_blocks];

    for(int i = 0; i < number_of_blocks; i++){
        if(i < 1 + free_blocks + fat_blocks + directory_blocks)
            free_table[i] = 0; // NOT FREE //
        else
            free_table[i] = 1; // FREE //
        fwrite(&free_table[i], sizeof(int), 1, file);
    }


    int fat_table[number_of_blocks];

    for(int i = 0; i < number_of_blocks; i++){
        fat_table[i] = -1;
        fwrite(&fat_table[i], sizeof(int), 1, file);
    }

    fwrite(&rootDir, sizeof(DirectoryEntry), 1, file);

    fseek(file, (directory_blocks - 1) * block_size, SEEK_SET);

    char buffer[block_size];

    for(int i = 0; i < number_of_blocks - fat_blocks - directory_blocks - free_blocks - 1; i++){
        fwrite(buffer, sizeof(char), block_size, file);
    }

    fclose(file);

    return 0;
}