#include "bot.hpp"
#include "irc.hpp"
#include <iostream>
#include <pthread.h>
#define ERROR(msg){\
 std::cout << msg << "\n"; \
 return 0;\
}
int main(int argCount,char**arguments)
{
if(argCount < 7)
  ERROR("./programm host port nick UserName RealName channel");
Bot bot(arguments[4],arguments[5],arguments[3],arguments[1],atoi(arguments[2]));
pthread_t BotHead;
bot.connect();
bot.JoinToChannel(arguments[6]);
bot.StartRead();
//void (test)(void)=&bot.connect;
//pthread_create(&BotHead,NULL,bot.connect,NULL);
}
