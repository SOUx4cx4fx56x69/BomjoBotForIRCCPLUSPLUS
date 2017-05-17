#include<stdio.h>
#include<stdlib.h>
#include <string.h>

char * _strtok(char*buffer,const char *what)
{
while(*buffer == 0) *buffer++;
//printf("%s\n",buffer);
size_t whatSize = strlen(what);
char * string = (char*)malloc(sizeof(char)*whatSize);
unsigned int i = 0;
while(*buffer)
{
for(int i = 0; i< whatSize;i++)
{
if(*buffer == *what) 
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
 free(buffer[0]);
 return 0;
}
return string;
}

char * _strdup(char*buffer)
{
unsigned int i = 0;
size_t bufferSize = strlen(buffer);
char * string = (char*)malloc(sizeof(char)*bufferSize);
while(*buffer)
 string[i++]=*buffer++;

return string;
}

void main()
{
while(1)
{
 char * test = _strdup("test 123 456 asdf adf 0 0 0 0 0 123 123 123123123 12312 3123123 123123 ");
 char * string = _strtok(test," ");
 while(string != 0)
 {
 printf("%s\n",string);
 string = _strtok(test," ");
 }
 free(test[0]);
}

}
