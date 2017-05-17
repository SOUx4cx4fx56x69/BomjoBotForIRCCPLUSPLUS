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
 bool BotCommand(char*nick,char*realname,char*adress,char*TypeMessage,char*channel,char*command);
 virtual void ReadMessage(char*msg);
};
