#include "bot.hpp"
#include "client.hpp"
#ifndef IRC_HPP
#define IRC_HPP
class IrcProtocol// : public Bot 
{
public:
 IrcProtocol(void);
 bool connect(int socket,constchr name,constchr UserName,constchr RealName);
};
#endif
