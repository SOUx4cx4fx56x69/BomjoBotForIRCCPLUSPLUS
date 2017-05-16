#include "irc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "util.hpp"
IrcProtocol::IrcProtocol(){};
bool IrcProtocol::connect(int socket,constchr name,constchr UserName,constchr RealName)
{
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
sprintf(buffer,"NICK %s",name);
if(! writeTo(socket,buffer) ) 
{
applog(ERROR,"Not can write to server");
free(buffer);
return false;
}
if(! readFrom(socket,buffer) ) 
{
applog(ERROR,"Not can read from server");
free(buffer);
return false;
}
printf("%s\n",buffer);
free(buffer);
}
