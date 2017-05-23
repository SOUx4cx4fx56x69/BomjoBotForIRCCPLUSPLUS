
#include "util.hpp"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
static bool debug = false;
unsigned int max_flt(void)
{
char tmp[256];
sprintf(tmp,"%f",FLT_MAX);
return _strlen(tmp);
}
void debug_on(int i)
{
if(i) debug=true;
}
void applog(short _type,const char*frmt,...)
{
if(_type == DEBUG && !debug);//shitcodeonelove
else
{
time_t tim;
time(&tim);
struct tm* time_info;
time_info = localtime(&tim);
char time_tmp[26];
char buffer[36];
strftime(time_tmp, 26, "[%Y-%m-%d %H:%M:%S]", time_info);

va_list ap;
char * arg;
va_start(ap, frmt);

switch(_type)
{
//default:
case INFO:
 sprintf(buffer,"%sINFO: ",time_tmp);
 fprintf(stdout,"%s",buffer);
 vfprintf (stdout,frmt, ap);
break;
case WARNING:
 sprintf(buffer,"%sWARNING: ",time_tmp);
 fprintf(stderr,"%s",buffer);
 vfprintf (stderr, frmt, ap);
break;
case ERROR:
 sprintf(buffer,"%sERROR: ",time_tmp);
 fprintf(stderr,"%s",buffer);
 vfprintf (stderr, frmt, ap);
break;
case DEBUG:
 sprintf(buffer,"%sDEBUG: ",time_tmp);
 fprintf(stdout,"%s",buffer);
 vfprintf (stdout, frmt, ap);
break;

}
puts("");
}

}
long CountChar(char*buffer,char ch)
{
   long count=-1;
   while(*buffer)
   {
	//printf("%c %c \n",*buffer,ch);
      if(*buffer==ch)count++;
      *buffer++;
   }
return count == -1 ? -1 : count+1;
}
long paramsComand(char*buffer,char ch)
{
   long count;
   while(*buffer && *buffer != ch )
   {
      *buffer++;
      count++;
   }
   if(*buffer == ch) return count;
   return -1;
}
long FindWhere(const char*buffer,const char*string)
{
//printf("%s\n",buffer);
unsigned long count=0;
while(*buffer)
 {
   if(*buffer == *string)
   {
    while(*buffer == *string && *string)
    {
     *buffer++;
     *string++;
    }

    if(!*string) return count;
   }
  count++;
 *buffer++;
 }

if(!*buffer) return -1;
}

size_t _strlen(const char*str)
{
int counter=0;
while(*str++)counter++;
return counter;
}

char * _copy_string(const char*str)
{
size_t sizeString = _strlen(str);
char * string = (char*)malloc( sizeof(char) * sizeString );
for(size_t i = sizeString;i--;)
 string[i]=str[i];

string[sizeString]='\0';
return string;
}
/*
char * _strtok(char*buffer,const char *what)
{
while(*buffer == 0) *buffer++;
//printf("%s\n",buffer);
size_t whatSize = _strlen(what);
char * string = (char*)malloc(sizeof(char)*whatSize);
unsigned int i = 0;
while(*buffer)
{
for(int i = 0; i< whatSize;i++)
{
if(*buffer == what[i])
{
*buffer=0;
return string;
}
}
string[i++]=*buffer++;
*(buffer-1)=0;
}
if(!*buffer)
{
// free((void*)&buffer[0]);
 return 0;
}
return string;
}
*/
char * _strdup(char*buffer)
{
unsigned int i = 0;
size_t bufferSize = _strlen(buffer);
char * string = (char*)malloc(sizeof(char)*bufferSize);
while(*buffer)
 string[i++]=*buffer++;

return string;
}
