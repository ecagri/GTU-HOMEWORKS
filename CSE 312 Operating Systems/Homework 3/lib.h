#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAXSIZE 16 * 1024 * 1024
#define MAXNUMBEROFFILE 512

void errExit(char * message);

typedef struct DirectoryEntry{
    char filename[128];
    char parent[128];
    time_t last_modification;
    int size;
    int first_block;
    int directory;
    int exist = 0;
    DirectoryEntry(char filename[], char parent[], time_t last_modification, int size, int first_block, int directory);
    DirectoryEntry();
}DirectoryEntry;

typedef struct SuperBlock{
    int block_size;
    int number_of_blocks;
    int free_blocks;
    int fat_blocks;
    int directory_blocks;
    SuperBlock(int block_size, int number_of_blocks, int free_blocks, int fat_blocks, int directory_blocks);
    SuperBlock();
}SuperBlock;

#endif