#include "irc.hpp"
#include "bot.hpp"
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"util.hpp"

#define DEFAULT_SLEEP 1000000 // 1000000 / 1000 = 1000 microseconds

unsigned long _strlen(const char*str)
{
unsigned long counter;
while(*str++)counter++;
return counter;
}

char * _copy_string(const char*str)
{
char * string = (char*)malloc( sizeof(char) * _strlen(str) ); 
while(*str)
  *string++=*str++;


}

void Bot::PingPong(int socket)
{
 
}

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
if(Bot::port == 0 || Bot::host == 0) return false;
for(unsigned short i = Bot::recconect_max; i>0 && Bot::self_socket==0; i--)
 Bot::self_socket=InitClient(Bot::host,Bot::port);
if(Bot::self_socket==0) return false;
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

/*
 void SetUsername(char*username);
 void SetRealName(char*realname);
*/
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
IrcProtocol irc;
while(!irc.connect(Bot::self_socket,Bot::name,Bot::UserName,Bot::RealName)) Bot::Recconect();
}

bool Bot::Recconect(const char*host,unsigned int port)
{
for(unsigned short i = Bot::recconect_max; i>0 && Bot::self_socket==0; i--)
 Bot::self_socket=InitClient(host,port);
if(Bot::self_socket==0) return false;
Bot::host=_copy_string(host);
return true;
}

Bot::Bot(constchr name,constchr UserName,constchr RealName,constchr host,int port,unsigned short recconect_max)
{

Bot::self_socket=InitClient(host,port);
Bot::SetHost(host);
Bot::SetPort(port);
Bot::SetName(name);
Bot::SetUsername(UserName);
Bot::SetRealName(RealName);

while( !Bot::Recconect(host,port) ) usleep(DEFAULT_SLEEP);
applog(INFO,"Succefully connecting, start talking with a server");

}
