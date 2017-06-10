#include "bot.hpp"
#pragma once
class BotFunctions : private Bot
{
private:
 int self_socket;
 bool MessageUnderstanding(char*msg);
 static char ** Self_Commands;
public:
 BotFunctions(int socket);
bool BotCommand(const char*nick,const char*realname,const char*adress,const char*TypeMessage,const char*channel, const char*command);
 virtual void ReadMessage(char*msg);
};
