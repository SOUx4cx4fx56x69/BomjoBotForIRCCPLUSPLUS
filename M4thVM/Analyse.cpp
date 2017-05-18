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

const char * VirtualMachine::AnalyseString(const char * string)
{
 char * tmp = (char*)calloc(sizeof(char),MAXBUFFER);
 unsigned int counter=0;
 bool sign_before=false;
 bool two=false;
 while(*string && *string !=end_string)
 {
   while(*string && *string == ' ')*string++;
   switch(VirtualMachine::type_letters(*string))
   {
     case number:
     while(*string > 47 && *string < 58 || *string == '.' && *string && counter < MAXBUFFER-1)
     {
        if(sign_before && *string == '.' && !two)
        {
        applog(ERROR,"Parse error, much '.'");
        free(tmp);
        return 0;
        }
        if(*string == '.') sign_before=true;
        tmp[counter++]=*string++;
     }
     if(two)
     {
      two=false;
      //
     }
     else
     {
     two=true;
     //tmp[counter++]=' ';
     }
	  printf("number\n");
     break;

     case letter:
     /*
     while(*string && (VirtualMachine::type_letters(*(string+1)) == letter ))
     {

     }
     */
     while(*string && *string != VirtualMachine::set_char)
     {
        tmp[counter++]=*string++;
     }
     if(*string != VirtualMachine::set_char)
     {
       //code
       VirtualMachine::vars->name=_strdup(tmp);
     }
     else
     {
       tmp[counter++]='$';
       VirtualMachine::vars->name=_strdup(tmp-1);
       //code
     }
     printf("let %c\n",*string++);
     break;

     case math_letter:
     if(VirtualMachine::type_letters(*(string+1)) == math_letter )
     {
     applog(ERROR,"Parse error, after %c not must be yet math_letter %c",*string,*(string+1));
     free(tmp);
     return 0;
     }
     if(*string == '+' && counter < MAXBUFFER-1){
      tmp[counter++]='P';//Plus
      //tmp[counter++]=' ';
     }else if(*string=='-' && counter < MAXBUFFER-1) {
      tmp[counter++]='M';//Minus
      //tmp[counter++]=' ';
     }else if(*string=='*' && counter < MAXBUFFER-1){
      tmp[counter++]='I';//Increase
     }else if(*string=='/' && counter < MAXBUFFER-1){
      tmp[counter++]='D';//Divide
     }else if(*string=='%' && counter < MAXBUFFER-1){
      tmp[counter++]='L';//moduLe
     }else if(*string=='^' && counter < MAXBUFFER-1){
      tmp[counter++]='O';//pOw
     }
     else return 0;
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
 tmp[counter++]=';';
 return tmp;
}
