#include "bot.hpp"
#include "BotFunctions.hpp"
#include "util.hpp"
#include <stdlib.h>
#ifndef GET_PART
#define GET_PART(msg,ch,tmp,array){\
  while(*msg != ch && *msg)\
   array[tmp++] = *msg++;\
  tmp=0;\
  *msg++;\
}
#define GET_PART_WITHOUTCLEAR(msg,ch,tmp,array){\
  while(*msg != ch && *msg)\
   array[tmp++] = *msg++;\
  *msg++;\
}
#endif
BotFunctions::BotFunctions(){}
bool BotFunctions::MessageUnderstanding(char*msg)
{//shitcodeonelove

if(*msg != ':') return false;
size_t sizeString = _strlen(msg);
unsigned int RealNameWhere = FindWhere(msg,"!");
if(RealNameWhere == -1) return false;
unsigned int AdressWhere = FindWhere(msg,"@");
if(AdressWhere == -1) return false;
register volatile int tmp=0;
char * Nick = (char*)malloc(sizeof(char) *  RealNameWhere);
char * RealName = (char*)malloc(sizeof(char) *  sizeString-RealNameWhere);
char * Adress = (char*)malloc(sizeof(char) *  sizeString-AdressWhere);
  GET_PART(msg,'!',tmp,Nick);
  GET_PART(msg,'@',tmp,RealName);
//
  GET_PART_WITHOUTCLEAR(msg,' ',tmp,Adress)
  char * TypeMessage = (char*)malloc(sizeof(char) *  sizeString-(AdressWhere+tmp)); 
  tmp=0;
  GET_PART_WITHOUTCLEAR(msg,' ',tmp,TypeMessage);
  char * Message = (char*)malloc(sizeof(char) *  sizeString-(AdressWhere+tmp)); 
  tmp=0;
  GET_PART(msg,'\n',tmp,Message);
//
applog(INFO,"%s!%s@%s Write: (%s) %s ",Nick,RealName,Adress,TypeMessage,Message);
free(Nick);
free(RealName);
free(Adress);
free(TypeMessage);
free(Message);
}

void BotFunctions::ReadMessage(char*msg)
{
 if(FindWhere(msg,"PING") == 0) writeTo(Bot::self_socket,(char*)"PONG");
 BotFunctions::MessageUnderstanding(msg);
}
