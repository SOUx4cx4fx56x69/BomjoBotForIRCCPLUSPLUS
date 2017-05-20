#include "virtualMachine.hpp"
#include <stdio.h>
#include <stdlib.h>
#define MAXBUFFER 1024
/*
<Hypnosis> Coco/r учёные делали
<Francezgy> Ну блятьыа
<Hypnosis> это передний край науки
<Hypnosis> а все остальные делали наколенщики

NameVar=Number
+ - * /
*/
type VirtualMachine::type_letters(const char ch)
{
if(CountChar((char*)VirtualMachine::math_letters,ch) > 1) return (type)math_letter;
if(CountChar((char*)VirtualMachine::numbers,ch) > 1) return (type)number;
if(CountChar((char*)VirtualMachine::varsnameletters,ch) > 1 || ch == this->set_char  ) return (type)letter;
return (type)undefined;
}

unsigned const char * VirtualMachine::AnalyseString(const char * string)
{
 unsigned char * tmp = (unsigned char*)calloc(sizeof(char),MAXBUFFER);
 unsigned int counter=0;
 bool sign_before=false;
 bool msign=false;
 if(*string == '-'){
 tmp[counter++] = 8;
 *string++;
 }
 while(*string && *string !=end_string)
 {
   while(*string && *string == ' ')*string++;
   switch(VirtualMachine::type_letters(*string))
   {
     case number:
     while(*string > 47 && *string < 58 || *string == '.' && *string && counter < MAXBUFFER-1)
     {
        if(sign_before && *string == '.')
        {
        applog(ERROR,"Parse error, much '.'");
        free(tmp);
        return 0;
        }
        if(*string == '.') sign_before=true;
        tmp[counter++]=*string++;
     }
	  printf("number\n");
     break;
     case letter:
     while(*string && (VirtualMachine::type_letters(*(string+1)) == letter ))
     {
        tmp[counter++]=*string++;
     }
     if(*string == this->set_char)
     {
      // tmp[counter++]='$';
      tmp[counter++]=7;
     }
     printf("let %c\n",*string++);
     break;

     case math_letter:
     if(*(string+1) == '-' && !msign)
     {
        msign=true;
        tmp[counter++]=8;
        *string++;
     }
     if(VirtualMachine::type_letters(*(string+1)) == math_letter )
     {
     applog(ERROR,"Parse error, after %c not must be yet math_letter %c",*string,*(string+1));
     free(tmp);
     return 0;
     }
     if(*string == '+' && counter < MAXBUFFER-1){
      //tmp[counter++]='P';//Plus
      tmp[counter++]=1;
      //tmp[counter++]=' ';
     }else if(*string=='-' && counter < MAXBUFFER-1) {
      //tmp[counter++]='M';//Minus
      tmp[counter++]=2;
      //tmp[counter++]=' ';
     }else if(*string=='*' && counter < MAXBUFFER-1){
      tmp[counter++]=3;
      //tmp[counter++]='I';//Increase
     }else if(*string=='/' && counter < MAXBUFFER-1){
      tmp[counter++]=4;
      //tmp[counter++]='D';//Divide
     }else if(*string=='%' && counter < MAXBUFFER-1){
      //tmp[counter++]='L';//moduLe
      tmp[counter++]=5;
     }else if(*string=='^' && counter < MAXBUFFER-1){
      tmp[counter++]=6;
      //tmp[counter++]='O';//pOw
     }
     else return 0;
     msign=false;
     sign_before=false;
     *string++;
     printf("math %c\n",*string);
     break;

     default:
     applog(ERROR,"Parse error, undefined char %c",*string);
     free(tmp);
     return 0;
     break;
   }
 }
 tmp[counter++]=this->end_some_math_operation;
 return tmp;
}
