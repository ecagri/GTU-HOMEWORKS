#include <multitasking.h>

using namespace myos;
using namespace myos::common;

void printf(char*);
void int_to_string(int, char*);

Task::Task(GlobalDescriptorTable *gdt, void entrypoint(), char * name)
{
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;
    
    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */
    
    // cpustate -> error = 0;    
   
    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;
    this->name = name;
    this->status = RUNNING;
    
}

Task::~Task()
{
}

char * Task::getName(){
  return this->name;
}

void Task::start(){
  this->status = RUNNING;
}
  
TaskManager::TaskManager()
{
    numTasks = 0;
    currentTask = -1;
    initial = true;
}

TaskManager::~TaskManager()
{
}

void TaskManager::terminateTask(Task * task){
 task->status = TERMINATED; 
  
}

void TaskManager::printTasks(){
    printf("\nPROCESS TABLE\n");
    for(int i = 0; i < numTasks; i++){
      char * str;
      int_to_string(i, str);
      printf(str);
      printf("  ");
      printf(tasks[i]->getName());
      printf("\n");
    }
}

int TaskManager::getNumTasks(){
  return numTasks;
}


bool TaskManager::AddTask(Task* task)
{
    printf(task->name);
    printf(" is added.\n");
    if(numTasks >= 256)
      return false;
    task->status = RUNNING;
    tasks[numTasks++] = task;
    return true;
}

void TaskManager::stopAllProcesses(){
  for(int i = 0; i < numTasks; i++){
    terminateTask(tasks[i]);
  }
  
}

CPUState* TaskManager::Schedule(CPUState* cpustate)
{
    if(numTasks <= 0){
      if(initial == true){
	  init = cpustate;
	  initial = false;
      }
      else{
	cpustate = init;
      }
      return cpustate;
    }
    
    if(currentTask >= 0)
        tasks[currentTask]->cpustate = cpustate;
    
    if(++currentTask >= numTasks)
        currentTask %= numTasks;
    
    if(tasks[currentTask]->status == TERMINATED){
      stopTask(tasks[currentTask]);
      if(numTasks<= 0){
	cpustate = init;
      }
      return Schedule(cpustate);
    }
    
    return tasks[currentTask]->cpustate;
}

void TaskManager::stopTask(Task * task){
    for(int i = 0; i < numTasks; i++){
	if(tasks[i] == task){
	    for(int j = i; j < numTasks; j++){
	      tasks[j] = tasks[j+1];
	    }
	    numTasks--;
	}
    }
}

    