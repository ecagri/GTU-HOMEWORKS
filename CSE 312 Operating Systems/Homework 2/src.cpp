#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <limits.h>
#include <string.h>

int ** physicalMemory, **virtualMemory;
int physicalMemorySize, virtualMemorySize, frameSize, period;
char * diskFileName;

typedef struct {
    bool valid = false;
    bool referenced = false;
    bool modified = false;
    int old = 0;
    unsigned int page_frame = -1;
}PageTableEntry;

typedef enum{
    SC,
    LRU,
    WSClock
}PageReplacementMode;

void createDisk(char * filename){
    FILE * fp = fopen(filename, "w");
    if(fp == NULL){
        printf("An error occured while opening the disk.\n");
        return;
    }
    for(int i = 0; i < virtualMemorySize; i++){
        for(int j = 0; j < frameSize; j++){
            fprintf(fp, "%d ", rand()%100);
        }
        fprintf(fp, "\n");
    }
}

void readPageFromDisk(char * filename, int pageNumberInDisk, int pageNumberInMemory){
    FILE * fp = fopen(filename, "r");
    if(fp == NULL){
        printf("An error occured while opening the disk.\n");
        return;
    }
    for(int i = 0; i < pageNumberInDisk; i++){
        while(fgetc(fp) != '\n'){

        }
    }
    
    for(int i = 0; i < frameSize; i++){
        int number;
        fscanf(fp, "%d", &number);
        physicalMemory[pageNumberInMemory][i] = number;
    }
    fclose(fp);
}

void writePageToDisk(char * filename, int pageNumberInDisk, int pageNumberInMemory){
    FILE * fp = fopen(filename, "r");
    char c;
    if(fp == NULL){
        printf("An error occured while opening the disk.\n");
        return;
    }
    FILE * temp = fopen("temp.dat", "w");
    if(temp == NULL){
        printf("An error occured while opening a temp file.\n");
    }
    for(int i = 0; i < pageNumberInDisk; i++){
        while((c = fgetc(fp)) != '\n'){
            fputc(c, temp);
        }
        fputc('\n', temp);
    }
    for(int i = 0; i < frameSize; i++){
        fprintf(temp, "%d ", physicalMemory[pageNumberInMemory][i]);
    }
    fprintf(temp, "\n");

    while(fgetc(fp) != '\n'){

    }

    while((c = fgetc(fp)) != EOF){
        fputc(c, temp);
    }
    fclose(fp);
    fclose(temp);

    remove(filename);

    rename("temp.dat", filename);
    
}

class PageTable{
    private: 
        PageTableEntry * pageTableEntries;
        PageReplacementMode mode;
        int counter = 1, pageFault = 0, pageReplacement = 0, read = 0, write = 0, readFromDisk = 0, writeToDisk = 0;
    public:
        PageTable(int size, PageReplacementMode mode){
            this->pageTableEntries = new PageTableEntry[size];
            this->mode = mode;
        }
        ~PageTable(){
            delete[] this->pageTableEntries;
        }

        int secondChance(int minOld){
            int pageReplaced, min = INT_MAX;
            for(int i = 0; i < virtualMemorySize; i++){
                if(this->pageTableEntries[i].valid && this->pageTableEntries[i].old < min && this->pageTableEntries[i].old >= minOld){
                    min = this->pageTableEntries[i].old;
                    pageReplaced = i;
                }
            }
            if(this->pageTableEntries[pageReplaced].referenced){
                this->pageTableEntries[pageReplaced].referenced = false;
                return secondChance(minOld + 1);
            }
            return pageTableEntries[pageReplaced].page_frame;
        }

        int leastRecentlyUsed(){
            int pageReplaced, min = INT_MAX;
            for(int i = 0; i < virtualMemorySize; i++){
                if(this->pageTableEntries[i].valid && this->pageTableEntries[i].old < min){
                    min = this->pageTableEntries[i].old;
                    pageReplaced = i;
                }
            }
            return pageTableEntries[pageReplaced].page_frame;
        }

        void paging(int pageNumber){
            if(!this->pageTableEntries[pageNumber].valid){ /* Page fault. */
                pageFault++;
                int properPage = -1;
                for(int i = 0; i < physicalMemorySize && properPage == -1; i++){
                    if(physicalMemory[i][0] == -1){ /* There is available spot in the physical memory. */
                        properPage = i;
                    }
                }
                if(properPage == -1){ /* There is no availabale spor in the physical memory. */
                    pageReplacement++;
                    if(mode == SC){ /* Second Chance. */
                        properPage = secondChance(1);
                    }else if(mode == LRU){ /* Least Recently Used. */
                        properPage = leastRecentlyUsed();
                    }else{ /* Working Set Clock. */
                    }
                }

                for(int i = 0; i < virtualMemorySize; i++){
                    if(this->pageTableEntries[i].page_frame == properPage){
                        this->pageTableEntries[i].valid = false;
                        if(this->pageTableEntries[i].modified){
                            pageTableEntries[i].valid = false;
                            pageTableEntries[i].modified = false;
                            pageTableEntries[i].referenced = false;
                            writeToDisk++;
                            writePageToDisk(diskFileName, i, properPage);
                        }
                        break;
                    }
                }

                readFromDisk++;
                readPageFromDisk(diskFileName, pageNumber, properPage);
                this->pageTableEntries[pageNumber].valid = true;
                this->pageTableEntries[pageNumber].page_frame = properPage;
                this->pageTableEntries[pageNumber].old = counter++;
            }else{
                read++;
                this->pageTableEntries[pageNumber].referenced = true;
                if(mode == LRU){
                    this->pageTableEntries[pageNumber].old = counter++;
                }
            }
        }

        void print(){
            printf("###### PAGE TABLE ######\n");
            printf("Valid  Referenced  Modified  Old PageFrame\n");

            for(int i = 0; i < virtualMemorySize; i++){
                printf("  %d         %d         %d      %d    %d\n", this->pageTableEntries[i].valid, this->pageTableEntries[i].referenced, this->pageTableEntries[i].modified, this->pageTableEntries[i].old, this->pageTableEntries[i].page_frame);
            }

            printf("$$$$$ END $$$$$\n");
        }

        void printStatistics(){
            printf("%d number of reads\n%d number of writes\n%d number of page misses\n%d number of page replacements\n%d number of disk page reads\n%d number of disk page writes\n", read, write, pageFault, pageReplacement, readFromDisk, writeToDisk);
        }

        int get(int page, int offset){
            read++;
            paging(page);
            return physicalMemory[pageTableEntries[page].page_frame][offset];
        }
        void set(int page, int offset, int value){
            write++;
            paging(page);
            physicalMemory[pageTableEntries[page].page_frame][offset] = value;
            pageTableEntries[page].modified = true;
        }
};


int main(int argc, char * argv[]){

    if(argc < 7){
        printf("Insufficient number of arguments...\n");
        return -1;
    }
    
    frameSize = pow(2, atoi(argv[1]));

    physicalMemorySize = pow(2, atoi(argv[2]));

    virtualMemorySize = pow(2, atoi(argv[3]));

    physicalMemory = new int*[physicalMemorySize];

    char * mode = argv[4];

    char * pageTableType = argv[5];

    period = atoi(argv[6]);

    diskFileName = argv[7];

    PageReplacementMode pageReplacementMode;

    if(strncmp(mode, "WSClock", 7) == 0){
        pageReplacementMode = WSClock;
    }else if(strncmp(mode, "LRU", 3) == 0){
        pageReplacementMode = LRU;
    }else{
        pageReplacementMode = SC;
    }

    PageTable pageTable(virtualMemorySize, pageReplacementMode);

    for(int i = 0; i < physicalMemorySize; i++){
        physicalMemory[i] = new int[frameSize];
        for(int j = 0; j < frameSize; j++){
            physicalMemory[i][j] = -1;
        }
    }

    createDisk(diskFileName);

    int row = 128, col = virtualMemorySize;

    int array[row][col], vector[col];

    int page = 0, counter = 0;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++, counter++){
            if(counter == frameSize){
                page++;
                counter = 0;
            }
            array[i][j] = pageTable.get(page, counter);
        }
    }


    for(int i = 0; i < col; i++, counter++){
        if(counter == frameSize){
            page++;
            counter = 0;
        }
        vector[i] = pageTable.get(page, counter);
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++, counter++){
            if(counter == frameSize){
                page++;
                counter = 0;
            }
            pageTable.set(page, counter, array[i][j] * vector[j]);
        }
    }
    pageTable.print();

    pageTable.printStatistics();

    for(int i = 0; i < physicalMemorySize; i++){
        delete[] physicalMemory[i];
    }

    delete[] physicalMemory;

}