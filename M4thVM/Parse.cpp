#include "virtualMachine.hpp"
#include <stdio.h>
bool VirtualMachine::ParseString(const char * string)
{
const char * parse;
if(! (parse = VirtualMachine::AnalyseString(string))) return false;
printf("%s\n",parse);
/*
PLUS 1
MINUS 2
MULTIPL 3
DIVIDE 4
MODULE 5
POW 6
SET 7
GET auto
*/
}
