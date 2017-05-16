#include "util.hpp"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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
 sprintf(buffer,"%sDEBUG: ",time_tmp);
 fprintf(stdout,"%s",buffer);
 vfprintf (stdout, frmt, ap);
break;

}
puts("");
}
