#include "bot.hpp"
#include "BotFunctions.hpp"
#include "util.hpp"
BotFunctions::BotFunctions(){}

void BotFunctions::ReadMessage(char*msg)
{
 if(FindWhere(msg,"PING") == 0) writeTo(Bot::self_socket,(char*)"PONG");
 printf("%s\n",msg);
}
