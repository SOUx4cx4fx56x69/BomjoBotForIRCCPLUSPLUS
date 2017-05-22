#include "virtualMachine.hpp"
#include <stdio.h>
#include <math.h>
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
#define MINSIZE 100
#define ALLOCATE 15
#define GET_NUM(tmp,buf){\
tmp=getNum(parse);\
while((int)*buf > 47 && (int)*buf<58 || (int)*buf == '.' && *buf)buf++;\
buf--;\
}

float getNum(const unsigned char * buffer)
{
    float tmp=0.0f;
    bool after_sign=false;
    if((int)*buffer == '.') after_sign=true;
    
    while((int)*buffer > 47 && (int)*buffer<58 || (int)*buffer == '.' && *buffer)
    {
     if((int)*buffer == '.') after_sign=true;

      tmp*=10;
      tmp+=(int)(*buffer-48);
      //if(after_sign)result/=10; 
      buffer++;
    }
return tmp;
}

unsigned const char * VirtualMachine::ParseString(const char * string)
{
unsigned const char * parse;

float result = 0.0f;
float tmp = 0.0f;

short size_operands __attribute__( (aligned(32)) ) = 0; // ~1024
short size_numbers __attribute__( (aligned(32)) ) = 0; // ~1024

char * operands = (char*)calloc(sizeof(char),MINSIZE);
float * numbers = (float*)calloc(sizeof(float),MINSIZE);

if(! (parse = VirtualMachine::AnalyseString(string))) return 0;
unsigned long i = 0;
while(*parse)
{
   if(*parse == this->end_some_math_operation) break;
//printf("%d\n",*parse);
   if((int)*parse > 47 && (int)*parse<58 || (int)*parse == '.')
   {//numbers
	GET_NUM(tmp,parse);
	numbers[size_numbers-1]=tmp;
	size_numbers++;
	if(size_numbers>=MINSIZE)
	 numbers = (float*)realloc(numbers,size_numbers+ALLOCATE);
   }else if( ( (int)*parse >= 65 && (int)*parse <= 90 ) || //A-Z OR a-z
             ( (int)*parse>=97 && (int)*parse <= 122)){//vars
	printf("\nVar: %c\n",*parse++);
   }else if( (int)*parse >=1 && (int)*parse <=8)
   {//math
 	operands[size_operands-1]=*parse;
	size_operands++;
	if(size_operands>=MINSIZE)
	 operands = (char*)realloc(operands,size_operands+ALLOCATE);
   }
   else
   {
     printf("undefined char -- %d\n",*parse);
     applog(ERROR,"Undefined type(VirtualMachine::ParseString). Stop calculating.");
     return 0;
   } 
   //printf("%c",*parse);
   *parse++;
}
for(short i = size_operands;i--;)
 printf("\nOPERAND->%c\n",operands[i]);
for(short i = size_numbers;i--;)
 printf("\nNUMBER->%f\n",numbers[i]);
this->sum=result;
puts("");

}
