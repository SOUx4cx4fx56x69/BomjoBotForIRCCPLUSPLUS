#include "bot.hpp"
#include "irc.hpp"
#include <iostream>
//#include <pthread.h>

#include <thread>
#define ERROR(msg){\
 std::cout << msg << "\n"; \
 return 0;\
}

int main(int argCount,char**arguments)
{
if(argCount < 7)
  ERROR("./programm host port nick UserName RealName channel");
Bot bot(arguments[3],arguments[4],arguments[5],arguments[1],atoi(arguments[2]));
std::thread Read_Thread;

bot.connect();
bot.JoinToChannel(arguments[6]);
Read_Thread = bot.StartRead();
Read_Thread.join();
//while(1);
//void (test)(void)=&bot.connect;
//pthread_create(&BotHead,NULL,bot.connect,NULL);



}
