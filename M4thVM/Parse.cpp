#include "virtualMachine.hpp"
#include <stdio.h>
#include <math.h>
#include <float.h>
//#include <limits.h>

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
counter++;\
if(counter >= this->MAX_NUM)\
{\
     applog(ERROR,"Very bit number....(in future version...)");\
     return 0;\
}\
tmp=getNum(parse);\
counter=0;\
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
unsigned int counter=0;
short size_operands __attribute__( (aligned(32)) ) = 1; // ~1024
short size_numbers __attribute__( (aligned(32)) ) = 1; // ~1024

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
    // printf("undefined char -- %d\n",*parse);
     applog(ERROR,"Undefined type(VirtualMachine::ParseString). Stop calculating.");
     return 0;
   } 
   //printf("%c",*parse);
   *parse++;
}

/*
for(short i = size_operands;i--;)
{
here be priority
}
*/

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
#warning NOT CORRECTLY almost
for(short i = 0;i<size_numbers;i++)
{
printf("Operands %d\n Num %f\n",operands[i],numbers[i]);
if(i+1>size_numbers)
tmp = numbers[i-1];
else
tmp = numbers[i];
if(operands[i] == 1)
{
 result+=tmp+numbers[i+1];
 numbers[i+1]=0.0f;
}else if(operands[i] == 2){
 result+=tmp-numbers[i+1];
 numbers[i+1]=0.0f;
}else if(operands[i] == 3){
 printf("%f\n",result);
 result+=tmp*numbers[i+1];
 printf("%f\n",result);
}else if(operands[i] == 4){
 if(numbers[i+1]==0 || tmp==0)
 {
  applog(ERROR,"not allow divide on zero...");
  result=0;
  break;
 }
 result+=tmp/numbers[i+1];
}else if(operands[i] == 5){
 if(numbers[i+1]==0 || tmp==0)
 {
  applog(ERROR,"not allow divide on zero...");
  result=0;
  break;
 }
 result+=((long long)tmp % (long long)numbers[i+1]);
 //numbers[i+1]=0.0f;
}
/*
else if(operands[i] == 6){
 result+=tmp-numbers[i+1];
 numbers[i+1]=0.0f;
}else if(operands[i] == 7){
 result+=tmp-numbers[i+1];
 numbers[i+1]=0.0f;
}*/
else if(operands[i] == 8){
 result*=-1;
 numbers[i+1]=0.0f;
}


}

this->sum=result;
puts("");

}
