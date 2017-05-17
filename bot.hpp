#include"util.hpp"
#include "irc.hpp"
#include <thread>

#ifndef BOT_HPP
#define BOT_HPP
class Bot : public IrcProtocol
{
private:
 unsigned short recconect_max;
 char * host;
 unsigned int port;
 char* name;
 char * UserName;
 char * RealName;
 char * defaultChannel;
 void PingPong(int second);
 int self_socket;
public:
 std::thread StartPingPongThread(int second);
 Bot(constchr name,constchr UserName,constchr RealName,constchr host,int port,unsigned short recconect_max=MAX_RECCONECT);
 Bot(void);
 void connect(void);
 bool JoinToChannel(char*channel);
 std::thread StartRead(void);
 void Read(void);
protected:
 void WriteMessage(char*msg);
 void WriteMessage(int socket,char*msg);
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
