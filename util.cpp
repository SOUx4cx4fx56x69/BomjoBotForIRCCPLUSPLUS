#include "util.hpp"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
static bool debug = false;
void debug_on(int i)
{
if(i) debug=true;
}
void applog(short _type,const char*frmt,...)
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
if(!debug) break;
 sprintf(buffer,"%sDEBUG: ",time_tmp);
 fprintf(stdout,"%s",buffer);
 vfprintf (stdout, frmt, ap);
break;

}
puts("");
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
unsigned long counter=0;
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

