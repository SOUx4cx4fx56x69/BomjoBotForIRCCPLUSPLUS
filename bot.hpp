#include"util.hpp"
#include "irc.hpp"
#pragma once
#ifndef BOT_HPP
#define BOT_HPP
class Bot : public IrcProtocol
{
private:
 unsigned short recconect_max; 
 int self_socket;
 char * host;
 unsigned int port;
 char* name;
 char * UserName; 
 char * RealName;
 char * defaultChannel;
public:
 Bot(constchr name,constchr UserName,constchr RealName,constchr host,int port,unsigned short recconect_max=MAX_RECCONECT);
 void connect(void);
 bool JoinToChannel(char*channel);
 void StartRead(void);
protected:
 bool Recconect(void);
 bool Recconect(const char * host, int port);
 constchr GetHost(void);
 constchr GetName(void);
 unsigned int GetPort(void);
 unsigned short GetMaxRecconect(void);
 void SetHost(constchr host);
 void SetName(constchr name);
 void SetPort(unsigned int port);
 void SetRecconectMax(unsigned short recconect_max);
 void SetUsername(constchr username);
 void SetRealName(constchr realname);
 void SetDefaultChannel(const char*channel);
};
#endif

