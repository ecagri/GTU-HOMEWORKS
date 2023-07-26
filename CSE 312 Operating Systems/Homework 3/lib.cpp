#include "lib.h"

DirectoryEntry::DirectoryEntry(char filename[], char parent[], time_t last_modification, int size, int first_block, int directory){
    strcpy(this->filename, filename);
    strcpy(this->parent, parent);
    this->last_modification = last_modification;
    this->size = size;
    this->first_block = first_block;
    this->directory = directory;
    this->exist = 999;
}

DirectoryEntry::DirectoryEntry(){}

SuperBlock::SuperBlock(int block_size, int number_of_blocks, int free_blocks, int fat_blocks, int directory_blocks){
    this->block_size = block_size;
    this->number_of_blocks = number_of_blocks;
    this->free_blocks = free_blocks;
    this->fat_blocks = fat_blocks;
    this->directory_blocks = directory_blocks;
}

SuperBlock::SuperBlock(){}
