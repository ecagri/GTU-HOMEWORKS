
#include <common/types.h>
#include <gdt.h>
#include <memorymanagement.h>
#include <hardwarecommunication/interrupts.h>
#include <syscalls.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <drivers/ata.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <multitasking.h>

#include <drivers/amd_am79c973.h>

#define __NR_fork 2


// #define GRAPHICSMODE


using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;
using namespace myos::gui;

void testBinarySearch();
void testLinearSearch();
void taskCollatz();
void taskInit1();
void cleanScreen(uint16_t*);
GlobalDescriptorTable gdt;
TaskManager taskManager;
InterruptManager interrupts(0x20, &gdt, &taskManager);
SyscallHandler syscalls(&interrupts, 0x80);
Task task1(&gdt, taskCollatz, "Collatz");
Task task2(&gdt, testBinarySearch, "BinarySearch");
Task task3(&gdt, testLinearSearch, "LinearSearch");

uint16_t* VideoMemory = (uint16_t*)0xb8000;
uint8_t x=0,y=0;

void printf(char* str)
{
    



    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
	  cleanScreen(VideoMemory);
	  x = 0;
	  y = 0;
        }
    }
}

void cleanScreen(uint16_t* VideoMemory){
  for(int y = 0; y < 25; y++)
    for(int x = 0; x < 80; x++)
      VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
   
}

void int_to_string(int num, char* str) {
    int i = 0;
    int sign = 0;

    if (num < 0) {
        sign = 1;
        num = -num;
    }

    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    if (sign) {
        str[i++] = '-';
    }

    str[i] = '\0';
    
    int len = i;
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void printfHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    printf(foo);
}
void printfHex16(uint16_t key)
{
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}
void printfHex32(uint32_t key)
{
    printfHex((key >> 24) & 0xFF);
    printfHex((key >> 16) & 0xFF);
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}





class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
      switch(c){
	case 'a':{
	  taskManager.stopAllProcesses();
	  Task task0(&gdt, taskInit1, "init");
	  taskManager.AddTask(&task0); 
	}break;
	case 'p':
	  taskManager.printTasks();
	  break;
      }
        char* foo = " ";
        foo[0] = c;
        printf(foo);
    }
};

class MouseToConsole : public MouseEventHandler
{
    int8_t x, y;
public:
    
    MouseToConsole()
    {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        x = 40;
        y = 12;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);        
    }
    
    virtual void OnMouseMove(int xoffset, int yoffset)
    {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);

        x += xoffset;
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y += yoffset;
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
    }
    
};




void sysprintf(char* str)
{
    asm("int $0x80" : : "a" (4), "b" (str));
    
}

void sysfork(){
    int32_t child_pid;
    asm("int $0x80": "=a" (child_pid) :  "a" (__NR_fork));
    if(child_pid == 0)
      printf("Child process");
    else if(child_pid > 0){
      printf("Parent process");
    }
}

void sysexecve(){
  
}

void syswaitpid(){
  
}

void taskInit1(){
  cleanScreen(VideoMemory);
  x=0, y=0;
  printf("CAGRI CAYCI OPERATING SYSTEM\n");
  taskManager.AddTask(&task1);
  taskManager.AddTask(&task2);
  taskManager.AddTask(&task3);
  while(true){ 
  }
}

void taskBinarySearch(int array[], int size, int key){
  int start = 0, end = size;
  
  while(start <= end){
    int middle = (start + end) / 2;
    
    if(array[middle] == key){
      char * number; 
      int_to_string(middle, number);
      printf(number);
      printf("\n");
     return;
    }
    else if(array[middle] < key){
      start = middle + 1;
    }
    
    else{
      end = middle - 1;
    }
  }  
}

void taskLinearSearch(int array[], int size, int key){
  for(int i = 0; i < size; i++){
    if(array[i] == key){
      char * index;
      
      int_to_string(i, index);
      
      printf(index);
      printf("\n");
      return;
    }
  }
  printf("-1\n");
}

void collatz(int number){
  char * current; 
  int_to_string(number, current);
  printf(current);
  printf("  ");
  if(number == 1){
    return;
  }
  
  if(number % 2 == 0){
    collatz(number / 2);
  }
  else{
    collatz(3 * number + 1);
  }
}

void taskCollatz(){
  int i = 1;
  while(true){  
    for(; i < 17; i++){
      char * index; 
      int_to_string(i, index);
      printf(index);
	
      printf(": ");
      collatz(i);
      printf("\n");
    }
    taskManager.terminateTask(&task1);
  }
}

void testBinarySearch(){
  int array[] = {10, 20, 30, 50, 60, 80, 100, 110, 130, 170};
  printf("The array is: ");
  for(int i = 0; i < 10; i++){
     char * str;
     int_to_string(array[i], str);
     printf(str);
     printf("  ");
  }
  printf("\nThe result of finding 110 by binary search is: ");
  
  int count = 0;
  while(true){
    if(count == 0)
      taskBinarySearch(array, 10, 110);
    
    taskManager.terminateTask(&task2);
    
    count++;
  }
}

void testLinearSearch(){
  int array[] = {10, 20, 30, 50, 60, 80, 100, 110, 130, 170};
  printf("The array is: ");
  for(int i = 0; i < 10; i++){
     char * str;
     int_to_string(array[i], str);
     printf(str);
     printf("  ");
  }
  printf("\nThe result of finding 175 by linear search is: ");
  int count = 0;
  while(true){
    if(count == 0)
      taskLinearSearch(array, 11, 175);
    
    taskManager.terminateTask(&task3);
    
    count++;
  }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
     
    uint32_t* memupper = (uint32_t*)(((size_t)multiboot_structure) + 8);
    size_t heap = 10*1024*1024;
    MemoryManager memoryManager(heap, (*memupper)*1024 - heap - 10*1024);
    
    printf("heap: 0x");
    printfHex((heap >> 24) & 0xFF);
    printfHex((heap >> 16) & 0xFF);
    printfHex((heap >> 8 ) & 0xFF);
    printfHex((heap      ) & 0xFF);
    
    void* allocated = memoryManager.malloc(1024);
    printf("\nallocated: 0x");
    printfHex(((size_t)allocated >> 24) & 0xFF);
    printfHex(((size_t)allocated >> 16) & 0xFF);
    printfHex(((size_t)allocated >> 8 ) & 0xFF);
    printfHex(((size_t)allocated      ) & 0xFF);
    printf("\n");
   
    
    printf("Initializing Hardware, Stage 1\n");
    
    #ifdef GRAPHICSMODE
        Desktop desktop(320,200, 0x00,0x00,0xA8);
    #endif
    
    DriverManager drvManager;
    
        #ifdef GRAPHICSMODE
            KeyboardDriver keyboard(&interrupts, &desktop);
        #else
            PrintfKeyboardEventHandler kbhandler;
            KeyboardDriver keyboard(&interrupts, &kbhandler);
        #endif
        drvManager.AddDriver(&keyboard);
        
    
        #ifdef GRAPHICSMODE
            MouseDriver mouse(&interrupts, &desktop);
        #else
            MouseToConsole mousehandler;
            MouseDriver mouse(&interrupts, &mousehandler);
        #endif
        drvManager.AddDriver(&mouse);
        
        PeripheralComponentInterconnectController PCIController;
        PCIController.SelectDrivers(&drvManager, &interrupts);

        #ifdef GRAPHICSMODE
            VideoGraphicsArray vga;
        #endif
        
    printf("Initializing Hardware, Stage 2\n");
        drvManager.ActivateAll();
        
    printf("Initializing Hardware, Stage 3\n");

    #ifdef GRAPHICSMODE
        vga.SetMode(320,200,8);
        Window win1(&desktop, 10,10,20,20, 0xA8,0x00,0x00);
        desktop.AddChild(&win1);
        Window win2(&desktop, 40,15,30,30, 0x00,0xA8,0x00);
        desktop.AddChild(&win2);
    #endif


    /*
    printf("\nS-ATA primary master: ");
    AdvancedTechnologyAttachment ata0m(true, 0x1F0);
    ata0m.Identify();
    
    printf("\nS-ATA primary slave: ");
    AdvancedTechnologyAttachment ata0s(false, 0x1F0);
    ata0s.Identify();
    ata0s.Write28(0, (uint8_t*)"http://www.AlgorithMan.de", 25);
    ata0s.Flush();
    ata0s.Read28(0, 25);
    
    printf("\nS-ATA secondary master: ");
    AdvancedTechnologyAttachment ata1m(true, 0x170);
    ata1m.Identify();
    
    printf("\nS-ATA secondary slave: ");
    AdvancedTechnologyAttachment ata1s(false, 0x170);
    ata1s.Identify();
    // third: 0x1E8
    // fourth: 0x168
    */
    
    
    amd_am79c973* eth0 = (amd_am79c973*)(drvManager.drivers[2]);
    eth0->Send((uint8_t*)"Hello Network", 13);
        

    interrupts.Activate();


    while(1)
    {
        #ifdef GRAPHICSMODE
            desktop.Draw(&vga);
        #endif
    }
    
    
    
}
