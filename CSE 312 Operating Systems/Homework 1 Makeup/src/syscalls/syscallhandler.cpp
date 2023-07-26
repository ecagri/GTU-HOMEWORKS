#include <syscalls/syscallhandler.h>

using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;

SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
    : InterruptHandler(interruptManager, InterruptNumber  + interruptManager->HardwareInterruptOffset()) {}

SyscallHandler::~SyscallHandler() {}

uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp;

    switch(cpu->eax)
    {
        case sys_fork:
	    cpu->eax = interruptManager->tableManager->Fork(cpu);
            break;
        case sys_waitpid:
	    cpu->eax = interruptManager->tableManager->GetStatus(cpu->ebx);
            break;
        case sys_exit:
	    interruptManager->tableManager->TerminateProcess(interruptManager->tableManager->GetCurrent(), cpu->ebx);
            break;
        default:
            break;
    }

    return esp;
}
