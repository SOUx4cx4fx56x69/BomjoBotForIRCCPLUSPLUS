#include "bot.hpp"
#include "BotFunctions.hpp"
#include "util.hpp"
#include <stdlib.h>
#include <string.h>
#ifndef GET_PART
#define GET_PART(msg,ch,tmp,array){\
   while(*msg != ch && *msg){\
    if(*msg == '\n')*msg++;\
    else array[tmp++] = *msg++;\
   }\
  array[tmp++]='\0';\
  tmp=0;\
  *msg++;\
}
#define GET_PART_WITHOUTCLEAR(msg,ch,tmp,array){\
  while(*msg != ch && *msg){\
   if(*msg == '\n')*msg++;\
   else array[tmp++] = *msg++;\
  }\
  array[tmp++]='\0';\
  *msg++;\
}
#endif

BotFunctions::BotFunctions(int socket)
{
   BotFunctions::self_socket=socket;
}

bool BotFunctions::BotCommand(char*nick,char*realname,char*adress,char*TypeMessage,char*channel,char*command)
{
*command++;
if(!*nick || !*realname || !*adress || !*command || !*TypeMessage || !*channel) return false;
size_t SizeString=_strlen(command);
if(SizeString == 0) return false;

bool CalledByUser=false;
if(*channel!='#')CalledByUser=true;
unsigned long paramsComand = CountChar(command,' ');


char ** Arguments = (char**)malloc(sizeof(char*) * paramsComand);
unsigned int t=0;

for(unsigned int i = paramsComand;i--;)
{
  printf("Allocate memory %d %d\n",i,SizeString);
  Arguments[i]=(char*)malloc(sizeof(char) * SizeString);
}
char * pch = strtok (command," ");
while (pch != NULL)
{
 Arguments[t++]=strdup(pch);
 pch = strtok (NULL, " ");
}
for(unsigned int i = t;i--;)
{
   printf("%s\n",Arguments[i]);
}
for(unsigned int i = paramsComand;i--;)
 free(Arguments[i]);
}

bool BotFunctions::MessageUnderstanding(char*msg)
{//shitcodeonelove

if(*msg != ':') return false;
*msg++;
size_t sizeString = _strlen(msg);
unsigned int RealNameWhere = FindWhere(msg,"!");
if(RealNameWhere == -1) return false;
unsigned int AdressWhere = FindWhere(msg,"@");
if(AdressWhere == -1) return false;
unsigned int ChannelWhere = FindWhere(msg,"#");

register volatile int tmp=0;
char * Nick = (char*)malloc(sizeof(char) *  RealNameWhere);
char * RealName = (char*)malloc(sizeof(char) *  sizeString-RealNameWhere);
char * Adress = (char*)malloc(sizeof(char) *  sizeString-AdressWhere);
char * channel;
  GET_PART(msg,'!',tmp,Nick);
  GET_PART(msg,'@',tmp,RealName);
//
  GET_PART_WITHOUTCLEAR(msg,' ',tmp,Adress)
  char * TypeMessage = (char*)malloc(sizeof(char) *  sizeString-(AdressWhere+tmp));
  tmp=0;
  GET_PART_WITHOUTCLEAR(msg,' ',tmp,TypeMessage);
  char * Message = (char*)malloc(sizeof(char) *  sizeString-(AdressWhere+tmp));
  tmp=0;

  if(ChannelWhere == -1)
  {
   channel = strdup(Nick);
  }
  else
  {
     channel = (char*)malloc(sizeof(char) *  sizeString-(ChannelWhere));
     GET_PART(msg,' ',tmp,channel);
  }
  tmp=0;
  GET_PART(msg,'\n',tmp,Message);
//
applog(INFO,"%s!%s@%s Write: (%s) %s %s",Nick,RealName,Adress,TypeMessage,channel,Message);
//
if(FindWhere(TypeMessage,"PRIVMSG")!=-1)
 BotFunctions::BotCommand(Nick,RealName,Adress,TypeMessage,channel,Message);
//
free(Nick);
free(RealName);
free(Adress);
free(TypeMessage);
free(Message);
free(channel);
}

void BotFunctions::ReadMessage(char*msg)
{
 if(FindWhere(msg,"PING") == 0) Bot::WriteMessage((char*)"PONG");
 BotFunctions::MessageUnderstanding(msg);
}
