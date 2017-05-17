#include "bot.hpp"
#pragma once
class BotFunctions : private Bot
{
private:
 int self_socket;
 bool MessageUnderstanding(char*msg);
public:
 BotFunctions(int socket);
 virtual void ReadMessage(char*msg);
};
