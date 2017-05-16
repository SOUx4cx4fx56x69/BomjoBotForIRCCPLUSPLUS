#include "client.hpp"
#include"util.hpp"
#define READFROMSOCKET(socket,buffer)\
if(! readFrom(socket,buffer) ) \
{\
applog(ERROR,"Not can read from server");\
free(buffer);\
return false;\
}

#define WRITETOSOCKET(socket,buffer)\
if(! writeTo(socket,buffer) ) \
{\
applog(ERROR,"Not can write to server");\
free(buffer);\
return false;\
}

#ifndef IRC_HPP
#define IRC_HPP
class IrcProtocol
{
private:
 char * NameHost;
protected:
 void PingPong(int socket,const char*buffer);
public:
 void setNameHost(const char * channel);
 bool JoinToChannel(int socket,const char * channel);
 //virtual void JoinToChannel(int,char*);
 IrcProtocol(void);
 bool connect(int socket,constchr name,constchr UserName,constchr RealName);
};
#endif
