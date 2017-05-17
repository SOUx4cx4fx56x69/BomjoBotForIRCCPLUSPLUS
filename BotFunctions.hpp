#include "bot.hpp"
#pragma once
class BotFunctions : private Bot
{
private:
 bool MessageUnderstanding(char*msg);
public:
 BotFunctions(void);
 virtual void ReadMessage(char*msg);
};
