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
#define GET_NUM(result,buf){\
result+=getNum(parse);\
while((int)*buf > 47 && (int)*buf<58 || (int)*buf == '.' && *buf)buf++;\
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
if(! (parse = VirtualMachine::AnalyseString(string))) return 0;
unsigned long i = 0;
while(*parse)
{
   if(*parse == this->end_some_math_operation) break;
   if((int)*parse > 47 && (int)*parse<58 || (int)*parse == '.')
   {//numbers
	//GET_NUM(result,parse,0);
	GET_NUM(result,parse);
	parse--;
   }else if( ( (int)*parse >= 65 && (int)*parse <= 90 ) || 
             ( (int)*parse>=97 && (int)*parse <= 122)) //A-Z OR a-z
   {//vars
	printf("\nVar: %c\n",*parse);
   }else if( (int)*parse >=1 && (int)*parse <=8)
   {//math
    switch((int)*parse)//alternative goto one love
    {
	case 1:
        //GET_NUM(result,parse,0);
	GET_NUM(result,parse);
	break;
	case 2:
	//GET_NUM(result,parse,1);
	break;
	case 3:
	break;
	case 4:
	break;
	case 5:
	break;
	case 6:
	break;
	case 7:
	break;
	case 8:
	break;
    }
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
this->sum=result;
puts("");

}
