#include "virtualMachine.hpp"
#include <stdio.h>
#include <stdlib.h>
VirtualMachine::VirtualMachine(void)
{
this->sum=0.0;
}

VirtualMachine::VirtualMachine(const char * string)
{
this->vars=(Machine_Vars*)malloc(sizeof(Machine_Vars)*DEFAULVARSALLOCATE);
this->sum=0;
this->ParseString(string);
}

float VirtualMachine::GetResult(void)
{
return this->sum;
}

int main(void)
{
char tmp[256];
while(1)
{
printf("~~~~~~~~~~\n");
fgets(tmp, sizeof(tmp), stdin);
VirtualMachine vm(tmp);
printf("%f\n",vm.GetResult());
}
}
