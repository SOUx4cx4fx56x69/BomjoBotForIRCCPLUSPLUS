#include "bot.hpp"
#include "BotFunctions.hpp"
#include "util.hpp"
#include <stdlib.h>
#include <string.h>
#ifndef GET_PART
#define GET_PART(msg,ch,tmp,array){\
  while(*msg != ch && *msg)\
   array[tmp++] = *msg++;\
  array[tmp++]='\0';\
  tmp=0;\
  *msg++;\
}
#define GET_PART_WITHOUTCLEAR(msg,ch,tmp,array){\
  while(*msg != ch && *msg)\
   array[tmp++] = *msg++;\
  array[tmp++]='\0';\
  *msg++;\
}
#endif

BotFunctions::BotFunctions(int socket)
{
   BotFunctions::self_socket=socket;
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
applog(INFO,"%s!%s@%s Write: (%s) %s %s ",Nick,RealName,Adress,TypeMessage,channel,Message);
if(FindWhere(Message,"привет")!=-1)
{
   char tmp[SIZEBUFFER];
   sprintf(tmp,"PRIVMSG %s дратути, %s",channel,Nick);
   Bot::WriteMessage(BotFunctions::self_socket,tmp);
}
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
