#include "bot.hpp"
#include "BotFunctions.hpp"
#include "util.hpp"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <fcntl.h>

#define STACKTMPSIZE 2056
#define CHANNELSIZE 33
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
const char help[] = 
"SAYTHIS (#channel optional) message;LEAVE #channel;JOINTO #channel;"
"WRITETOSERVER message;NICKSET nick;QUIT message;";
BotFunctions::BotFunctions(int socket)
{
   BotFunctions::self_socket=socket;
}

bool BotFunctions::BotCommand(const char*nick,const char*realname,const char*adress,const char*TypeMessage,const char*channel, const char*command)
{
*command++;
if(!*nick || !*realname || !*adress || !*command || !*TypeMessage || !*channel) return false;
size_t SizeString=_strlen(command);
if(SizeString == 0) return false;

//bool CalledByUser=false;
//if(*channel!='#')CalledByUser=true;
long paramsComand = CountChar((char*)command,' ');
if(paramsComand<=0)paramsComand=1;

char ** Arguments = (char**)malloc(sizeof(char*) * paramsComand);
unsigned int t=0;

for(unsigned int i = paramsComand;i--;)
  Arguments[i]=(char*)malloc(sizeof(char) * SizeString);

char * pch = strtok ((char*)command," ");
while (pch != NULL)
{
 Arguments[t++]=strdup(pch);
 pch = strtok (NULL, " ");
}
char tmp_bufffer[STACKTMPSIZE];
if(strcmp(Arguments[0],"SAYTHIS") == 0)
{
 if(Arguments[1][0] != '#')
 {
 // applog(DEBUG,"BotFunctions::BotCommand -> dont channel");
  sprintf(tmp_bufffer,"PRIVMSG %s",channel);
  for(unsigned int i = 1;i<t;i++)
  {
   sprintf(tmp_bufffer,"%s %s",tmp_bufffer,Arguments[i]);
  }
  writeTo(this->self_socket,tmp_bufffer);
 // applog(DEBUG,"BotFunctions::BotCommand -> Write to %s",tmp_bufffer);
 }
 else
 { 
  //shitcode one love
 // applog(DEBUG,"BotFunctions::BotCommand -> exist channel");
  unsigned int tmp_counter_channel=0;
  char tmp_channel_name[CHANNELSIZE];
  while(Arguments[1][tmp_counter_channel])
  {
   tmp_channel_name[tmp_counter_channel] = Arguments[1][tmp_counter_channel];
   tmp_counter_channel++;
  }
  tmp_channel_name[tmp_counter_channel]='\0';
  sprintf(tmp_bufffer,"PRIVMSG %s %s",tmp_channel_name,Arguments[2]);
 // applog(DEBUG,"BotFunctions::BotCommand -> Write to %s",tmp_bufffer);
  writeTo(this->self_socket,tmp_bufffer);
 }
}//if(strcmp(Arguments[0],"SAYTHIS") == 0)
else if(strcmp(Arguments[0],"LEAVE") == 0)
{
  sprintf(tmp_bufffer,"PART %s",Arguments[1]);
  writeTo(this->self_socket,tmp_bufffer);
}
else if(strcmp(Arguments[0],"JOINTO") == 0)
{
  sprintf(tmp_bufffer,"JOIN %s",Arguments[1]);
  writeTo(this->self_socket,tmp_bufffer);
}
else if(strcmp(Arguments[0],"QUIT") == 0)
{
  if(Arguments[1][0])
  {
  
  sprintf(tmp_bufffer,"QUIT ");
  for(unsigned int i = 1;i<t;i++)
   sprintf(tmp_bufffer,"%s%s",tmp_bufffer,Arguments[i]);
  
  }
  writeTo(this->self_socket,tmp_bufffer);
  raise(9);
}
else if(strcmp(Arguments[0],"WRITETOSERVER") == 0)
{
  for(unsigned int i = 1;i<t;i++)
  {
   sprintf(tmp_bufffer,"%s%s",tmp_bufffer,Arguments[i]);
  }
  writeTo(this->self_socket,tmp_bufffer);
}
else if(strcmp(Arguments[0],"NICKSET") == 0)
{
  sprintf(tmp_bufffer,"NICK %s",Arguments[1]);
  writeTo(this->self_socket,tmp_bufffer);
}
else if(strstr(Arguments[0],"HELP") != 0)
{
  sprintf(tmp_bufffer,"PRIVMSG %s %s",channel, help);
  writeTo(this->self_socket,tmp_bufffer);
  applog(DEBUG,"Write-> %s",tmp_bufffer);
}
bzero(tmp_bufffer,STACKTMPSIZE);

for(unsigned int i = 0;i< paramsComand;i++)
 free(Arguments[i]);
//free(Arguments);
}

void * BotFunctions::BotParseCommand(const char*nick,const char*realname,const char*adress,const char*TypeMessage,const char*channel, const char*command)
{

int file = open("commands.com",O_RDONLY);
if(file == -1) return (void*)-1;
out:
asm
(
"nop"
);
close(file);
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
bool TrueChannel = false;
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
   TrueChannel=true;
   while(*msg && *msg !=' ')*msg++;
  }
  else
  {
     channel = (char*)malloc(sizeof(char) *  sizeString-(ChannelWhere));
//     firstChannel=channel;
     GET_PART(msg,' ',tmp,channel);
  }
  tmp=0;
  //printf("%s\n",msg);
  GET_PART(msg,'\n',tmp,Message);
//
applog(INFO,"%s!%s@%s Write: (%s) %s %s",Nick,RealName,Adress,TypeMessage,channel,Message);
//
if(FindWhere(TypeMessage,"PRIVMSG")!=-1)
 BotFunctions::BotCommand(Nick,RealName,Adress,TypeMessage,channel,Message);

//BotFunctions::BotParseCommand(Nick,RealName,Adress,TypeMessage,channel,Message);
//else if(
//printf("Free\n");
// shitcode one love
free(Nick);
free(RealName);
free(Adress);
free(TypeMessage);
//free(Message);
//if(TrueChannel)
// free(channel);
}

void BotFunctions::ReadMessage(char*msg)
{
 if(FindWhere(msg,"PING") == 0) Bot::WriteMessage((char*)"PONG");
 BotFunctions::MessageUnderstanding(msg);
}
