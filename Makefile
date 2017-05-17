all:
	g++ client.cpp util.cpp bot.cpp AntiQubick.cpp irc.cpp BotFunctions.cpp -lpthread -o BotTest
clean:
	rm BotTest
