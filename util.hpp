#define SIZEBUFFER 1024
#define MAX_RECCONECT 5

typedef __SIZE_TYPE__ size_t;
typedef enum {INFO,WARNING,ERROR,DEBUG} _type;
void applog(short _type,const char*frmt,...);
long FindWhere(const char*buffer,const char*string);
size_t _strlen(const char*str);
char * _copy_string(const char*str);

#pragma once
typedef const char* constchr ;
