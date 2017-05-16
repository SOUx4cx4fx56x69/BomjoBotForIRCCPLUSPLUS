#include "bot.hpp"
#include "irc.hpp"
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"util.hpp"
#define IS_CONNECT()\
  if( !is_connect(Bot::self_socket) )\
  {\
  applog(ERROR,"Not can read from socket");\
  Bot::Recconect();\
  }
#define DEFAULT_SLEEP 15 // 1000000 / 1000 = 1000 microseconds
constchr Bot::GetName(void)
{
return Bot::name;
}

constchr Bot::GetHost(void)
{
return Bot::host;
}

unsigned int Bot::GetPort(void)
{
return Bot::port;
}

unsigned short Bot::GetMaxRecconect(void)
{
return Bot::recconect_max;
}

bool Bot::Recconect(void)
{
applog(DEBUG,"Recconect call.");
if(Bot::self_socket != 0) return true;
for(unsigned short i = Bot::recconect_max;i--;)
{
 close(Bot::self_socket);
 applog(DEBUG,"Recconecting.");
 Bot::self_socket=InitClient(Bot::host,Bot::port);

 Bot::connect();
 Bot::JoinToChannel(Bot::defaultChannel);
 IrcProtocol::JoinToChannel(Bot::self_socket,defaultChannel);

 if(Bot::self_socket!=0) break;
 sleep(DEFAULT_SLEEP);
}
if(Bot::self_socket == 0) return false;
return true;
}

void Bot::SetHost(constchr host)
{
Bot::host=_copy_string(host);
}

void Bot::SetName(constchr name)
{
Bot::name=_copy_string(name);
}

void Bot::SetPort(unsigned int port)
{
Bot::port=port;
}

void Bot::SetRecconectMax(unsigned short recconect_max)
{
Bot::recconect_max=recconect_max;
}

void Bot::SetDefaultChannel(const char * channel)
{
Bot::defaultChannel=_copy_string(channel);
}

void Bot::SetUsername(constchr username)
{
Bot::UserName=_copy_string(username);
}

void Bot::SetRealName(constchr realname)
{
Bot::RealName=_copy_string(realname);
}

void Bot::connect(void)
{
while(!IrcProtocol::connect(Bot::self_socket,Bot::name,Bot::UserName,Bot::RealName)) 
 while( !Bot::Recconect() );
}

bool Bot::Recconect(const char*host,int port)
{
applog(DEBUG,"Recconect call.");
if(Bot::self_socket != 0) return true;
for(unsigned short i = Bot::recconect_max;i--;)
{
 close(Bot::self_socket);
 applog(DEBUG,"Recconecting.");
 Bot::self_socket=InitClient(host,port);

 Bot::connect();
 Bot::JoinToChannel(Bot::defaultChannel);
 IrcProtocol::JoinToChannel(Bot::self_socket,defaultChannel);

 if(Bot::self_socket!=0) break;
 sleep(DEFAULT_SLEEP);
}
if(Bot::self_socket == 0) return false;
return true;
}

void Bot::StartRead(void)
{
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
while(1)
  {
  readFrom(Bot::self_socket,buffer);
  applog(DEBUG,"Read.");
  if(*buffer == 0)
 {
  close(Bot::self_socket);
  Bot::self_socket=0;
  Bot::Recconect();
 }
  else
  printf("%s\n",buffer);
  }
free(buffer);
}

bool Bot::JoinToChannel(char*channel)
{
 if(!IrcProtocol::JoinToChannel(Bot::self_socket , channel))
  while( !Bot::Recconect() );
}

Bot::Bot(constchr name,constchr UserName,constchr RealName,constchr host,int port,unsigned short recconect_max)
{
Bot::self_socket=InitClient(host,port);
Bot::recconect_max == 0 ? Bot::recconect_max=MAX_RECCONECT : recconect_max ;
Bot::SetHost(host);
Bot::SetPort(port);
Bot::SetName(name);
Bot::SetName(name);
Bot::SetUsername(UserName);
Bot::SetRealName(RealName);
while( !Bot::Recconect() );
}
