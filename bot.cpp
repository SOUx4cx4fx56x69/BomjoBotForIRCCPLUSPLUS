#include "bot.hpp"
#include "irc.hpp"
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"util.hpp"
#include "BotFunctions.hpp"
#include <thread>

#define DEFAULT_SLEEP 15 // 1000000 / 1000 = 1000 microseconds
#ifndef BOT_MUTEX
#define BOT_MUTEX
pthread_mutex_t Bot_Mutex;
#endif
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
pthread_mutex_lock(&Bot_Mutex);
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
pthread_mutex_unlock(&Bot_Mutex);
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
pthread_mutex_lock(&Bot_Mutex);
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
pthread_mutex_unlock(&Bot_Mutex);
if(Bot::self_socket == 0) return false;
return true;
}

std::thread Bot::StartRead(void)
{
applog(DEBUG,"std::thread Bot::StartRead");
std::thread Read_Thread(&Bot::Read, this);
return Read_Thread;
}
void Bot::WriteMessage(int socket,char*msg)
{
pthread_mutex_lock(&Bot_Mutex);
applog(DEBUG,"Write to server: %s",msg);
writeTo(socket,msg);
pthread_mutex_unlock(&Bot_Mutex);
}

void Bot::WriteMessage(char*msg)
{
pthread_mutex_lock(&Bot_Mutex);
applog(DEBUG,"Write to server: %s",msg);
writeTo(this->self_socket,msg);
pthread_mutex_unlock(&Bot_Mutex);
}

void Bot::PingPong(int second)
{
 while(1)
 {
  applog(DEBUG,"void Bot::PingPong(%d)",second);
  sleep(second);
  writeTo(Bot::self_socket,(char*)"PONG");
 }

}

std::thread Bot::StartPingPongThread(int second)
{
   applog(DEBUG,"std::thread Bot::StartPingPongThread(%d)",second);
 std::thread Ping_Pong_Thread(&Bot::PingPong, this,second);
 return Ping_Pong_Thread;
}
void Bot::Read(void)
{
applog(DEBUG,"Start thread read.");
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
BotFunctions Functions(Bot::self_socket);

while(1)
{
pthread_mutex_lock(&Bot_Mutex);
  readFrom(Bot::self_socket,buffer);
  applog(DEBUG,"Read.");
  //writeTo(Bot::self_socket,(char*)"PRIVMSG #ru test");
  if(*buffer == 0)
  {
  close(Bot::self_socket);
  Bot::self_socket=0;
  Bot::Recconect();
  }
  else
  {
   pthread_mutex_unlock(&Bot_Mutex);
   Functions.ReadMessage(buffer);
   pthread_mutex_lock(&Bot_Mutex);
  }
pthread_mutex_unlock(&Bot_Mutex);
}
free(buffer);
}

bool Bot::JoinToChannel(char*channel)
{
 if(!IrcProtocol::JoinToChannel(Bot::self_socket , channel))
  while( !Bot::Recconect() );
}
Bot::Bot(void){}
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
pthread_mutex_init(&Bot_Mutex,NULL);
}
