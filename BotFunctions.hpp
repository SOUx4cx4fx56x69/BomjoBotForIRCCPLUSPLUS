#include "bot.hpp"
#pragma once
class BotFunctions : private Bot
{
private:
public:
 BotFunctions(void);
 virtual void ReadMessage(char*msg);
};
