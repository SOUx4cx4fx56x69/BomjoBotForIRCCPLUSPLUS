#include "irc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.hpp"
IrcProtocol::IrcProtocol(){};



void IrcProtocol::PingPong(int socket,const char*buffer)
{
long Ping = FindWhere(buffer,"PING");
if(Ping == -1) 
 applog(INFO,"Server not have a ping-pong");
else
{
 while(*buffer && *buffer != ' ')
  *buffer++;
if(*buffer == ' ')
 {
  *buffer++;
  size_t sizeString = _strlen(buffer);
  char * ping = (char*)malloc(sizeof(char)*sizeString);
  size_t i;
  for(i = 0;i!=sizeString && *buffer !='\n';i++)
   ping[i] = *buffer++;
  ping[i++]='\0';
  i=0;
  char tmp[SIZEBUFFER];  
  sprintf(tmp,"PONG %s",ping);
  free(ping);
  applog(INFO,"Write to server: %s\n",tmp);
  writeTo(socket,tmp);
 }
}

}

bool IrcProtocol::connect(int socket,constchr name,constchr UserName,constchr RealName)
{
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
sprintf(buffer,"NICK %s",name);
WRITETOSOCKET(socket,buffer);
READFROMSOCKET(socket,buffer);
do{
applog(INFO,"Ping-Pong");
IrcProtocol::PingPong(socket,buffer);
sprintf(buffer,"USER %s 8 * : %s",UserName,RealName);
WRITETOSOCKET(socket,buffer);
READFROMSOCKET(socket,buffer);
}while( strstr(buffer,"nospoof") != NULL || strstr(buffer,"PING") != NULL  );
free(buffer);
}

bool IrcProtocol::JoinToChannel(int socket,const char * channel)
{
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
sprintf(buffer,"JOIN #%s",channel);
WRITETOSOCKET(socket,buffer);
}
