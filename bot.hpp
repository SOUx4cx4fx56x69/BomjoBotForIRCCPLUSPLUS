#define SIZEBUFFER 1024
#pragma once
typedef const char* constchr ;
class Bot
{
private:

 unsigned short recconect_max; 
 int self_socket;
 char * host;
 unsigned int port;
 char* name;
 char * UserName; 
 char * RealName;
public:
 Bot(constchr name,constchr UserName,constchr RealName,constchr host,int port,unsigned short recconect_max=5);
 void connect(void);
protected:
 bool Recconect(void);
 bool Recconect(const char * host, unsigned int port);
 void PingPong(int socket);
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
};
