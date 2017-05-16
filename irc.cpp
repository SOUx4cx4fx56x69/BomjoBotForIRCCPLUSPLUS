#include "irc.hpp"
#include <stdlib.h>
#include <stdio.h>
IrcProtocol::IrcProtocol(){};
bool IrcProtocol::connect(int socket,constchr name,constchr UserName,constchr RealName)
{
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
//sprintf(buffer,"NICK %s",name);
//if(!writeTo(Bot::self_socket,buffer)) return false;
if(! readFrom(socket,buffer) ) return false;

}
