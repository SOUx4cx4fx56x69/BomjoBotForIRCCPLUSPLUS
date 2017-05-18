#include "virtualMachine.hpp"
#include <stdio.h>
bool VirtualMachine::ParseString(const char * string)
{
const char * parse;
if(! (parse = VirtualMachine::AnalyseString(string))) return false;
printf("%s\n",parse);
/*
PLUS MINUS DIVIDE MODULE POW MULTIPLY GET SET
*/
}
