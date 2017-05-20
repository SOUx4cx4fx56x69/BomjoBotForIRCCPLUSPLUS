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
   if(*parse == this->end_some_math_operation) break;
   if((int)*parse > 47 && (int)*parse<58)
   {//numbers
    printf("\nNumber : %d\n",(int)*parse-48);
   }else if( ( (int)*parse >= 65 && (int)*parse <= 90 ) || 
             ( (int)*parse>=97 && (int)*parse <= 122)) //A-Z OR a-z
   {//vars
	printf("\nVar: %c\n",*parse);
   }else if( (int)*parse >=1 && (int)*parse <=8)
   {//math
    printf("\nMath %d\n",(int)*parse);
   }
   else
   {
     printf("undefined char -- %d\n",*parse);
     applog(ERROR,"Undefined type(VirtualMachine::ParseString). Stop calculating.");
     return 0;
   } 
   printf("%c",*parse);
   *parse++;
}
puts("");

}
