#include "virtualMachine.hpp"
#include <stdio.h>
/*
PLUS 1
MINUS 2
MULTIPL 3
DIVIDE 4
MODULE 5
POW 6
SET 7
GET auto
8 == (*-1)
*/
unsigned const char * VirtualMachine::ParseString(const char * string)
{
unsigned const char * parse;
if(! (parse = VirtualMachine::AnalyseString(string))) return 0;
unsigned long i = 0;
while(*parse)
{
   printf("%c",*parse);
   *parse++;
}
puts("");

}
