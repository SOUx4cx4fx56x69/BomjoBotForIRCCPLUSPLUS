#define SIZEBUFFER 1024
#define MAX_RECCONECT 5

typedef __SIZE_TYPE__ size_t;
typedef enum {INFO,WARNING,ERROR,DEBUG} _type;
void applog(short _type,const char*frmt,...);
long FindWhere(const char*buffer,const char*string);
size_t _strlen(const char*str);
char * _copy_string(const char*str);
void debug_on(int i);
long paramsComand(char*buffer,char ch);
long CountChar(char*buffer,char ch);
void add_string(char*buf,const char*string);
//char * _strtok(char*buffer,const char *what);
char * _strdup(char*buffer);
unsigned int max_flt(void);
#pragma once

typedef const char* constchr ;
