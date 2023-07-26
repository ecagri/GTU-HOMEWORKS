#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <syscalls/syscallhandler.h>
#include <lib/utility.h>
#include <multitasking/ProcessTable.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>

using namespace myos;
using namespace myos::drivers;
using namespace myos::common;
using namespace myos::hardwarecommunication;

GlobalDescriptorTable gdt;
ProcessTable processTable(&gdt);
InterruptManager interrupts(0x20, &gdt, &processTable);
SyscallHandler syscalls(&interrupts, 0x80);

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

uint32_t random_seed = 123456;

void initProcess();
void binarySearch();
void linearSearch();
void collatz();
uint32_t rand();

char buffer[2][80];
int buff_size[2] = {0, 0};
int currentBuffer = 0;

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
        char* foo = " ";
        foo[0] = c;
	if(c == 'p')
	  interrupts.ResetCounter();
	
	buffer[currentBuffer][buff_size[currentBuffer]] = c;
	buff_size[currentBuffer]++;
	
	if(c == '\n'){
	  buff_size[currentBuffer] = 0;
	}
	
        printf(foo);
    }
};


extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{

    processTable.CreateInitProcess(initProcess);
    interrupts.Activate();
    
    while(true);    // kernelMain is going ghost mode
}

void initProcess()
{
    printf("Init: Started. ");
    const uint32_t numOfProcess = 10;
    pid_t pids[numOfProcess];
    void (*process[])() = {binarySearch, linearSearch, collatz};
    uint32_t random = rand() % 3;
    
    printf("Forking's started ");
    for (uint32_t i = 0 ; i < numOfProcess ; ++i)
        pids[i] = fork(process[random]);
    printf("and finished. ");

    printf("Waiting child to terminate.\n");
    for (uint32_t i = 0 ; i < numOfProcess ; ++i)
        waitpid(pids[i]);
    printf("Init: All child finished and collected. Init is exiting...");

    exit(exit_success);
}

void interractUser(int ** arr, int * arrSize, int * key, int bufferNo){
  int length = 0, array[80];
  char toInt[80];
  
  buff_size[bufferNo] = 0;
	
  printf("\nEnter the array elements: ");
  
  while(buffer[bufferNo][buff_size[bufferNo] - 1] != 's'){
      
  }
  buffer[bufferNo][buff_size[bufferNo] - 1] = '\0';
  
  for(int i = 0; i < buff_size[bufferNo]; i++){
    if('0' < buffer[bufferNo][i] && buffer[bufferNo][i] < '9'){
      toInt[length] = buffer[bufferNo][i];
      length++;
    }
    else{
      toInt[length] = '\0';
      length = 0;
      array[*arrSize] = strToInt(toInt);
      (*arrSize)++;
    }  
  }
  *arr = array;
  
  buff_size[bufferNo] = 0;
  
  printf("\nEnter the key: ");
  
  while(buffer[bufferNo][buff_size[bufferNo] - 1] != 's'){
    
  }
  buffer[bufferNo][buff_size[bufferNo] - 1] = '\0';
	  
  *key = strToInt(buffer[bufferNo]);
}

void binarySearch()
{
  int * arr, arrSize = 0, key, low = 0, mid = 0, high = 0, index = -1;
  
  currentBuffer = 0;
  
  interractUser(&arr, &arrSize, &key, currentBuffer);
  
  high = arrSize - 1;
  
  while (low <= high){
    mid = (low + high) / 2;

    if (arr[mid] == key){
	index = mid;
	break;
    }
    else if (arr[mid] < key)
	low = mid + 1;
    else
	high = mid - 1;
  }

  int32_t printArr[] = {index};
  
  print("\nBinary search result: %d\n", 1, printArr);
  
  exit(exit_success);
}

void linearSearch()
{
    int * arr, arrSize = 0, key, low = 0, mid = 0, high = 0, index = -1;
    
    currentBuffer = 1;
  
    interractUser(&arr, &arrSize, &key, currentBuffer);
    
    high = arrSize - 1;

    for (uint32_t i = 0 ; i < arrSize ; ++i)
        if (arr[i] == key)
        {
            index = i;
            break;
        }
    
    int32_t printArr[] = {index};
    
    print("Linear search result: %d\n", 1, printArr);
    
    exit(exit_success);
}

void collatz()
{
    int32_t printArr[1];

    for (uint32_t i = 20 ; i < 25 ; ++i)
    {
        printArr[0] = i;
        print("Collatz %d: ", 1, printArr);
        uint32_t key = i;

        while (key != 1)
        {
            printArr[0] = key;
            print("%d, ", 1, printArr);

            if (key % 2 == 0)
                key /= 2;
            else
                key = key * 3 + 1;
        }

        printArr[0] = 1;
        print("%d\n", 1, printArr);
    }

    exit(exit_success);
}

uint32_t rand()
{
    random_seed = random_seed * 1103515245 + 12345;
    return random_seed;
}
