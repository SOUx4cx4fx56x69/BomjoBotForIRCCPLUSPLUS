#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#ifdef WIN32
   #include <winsock.h>
   #include <winsock2.h>
   #include <ws2tcpip.h>
   #define MSG_NOSIGNAL 0
   #pragma comment(lib, "ws2_32.lib")
#else
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
#endif
#include "bot.hpp"
#include "util.hpp"
int 
InitClient(const char*host,int portno)
{
    #ifdef WIN32
     WSADATA wsaData;
     DWORD dwError;
    // Initialize Winsock
    if ( (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) )
        error("WSAStartup failed\n");
    #endif
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if(sockfd == -1) 
	{
        applog(ERROR,"No can create socket");
	return 0;
	}
    server = gethostbyname(host);
    if (server == NULL)
    {
     applog(ERROR,"No such host");
     return 0;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
        applog(ERROR,"ERROR connecting");
	return 0;
	}
    return sockfd;
}
bool
writeTo(int socket,char*msg)
{
if(send(socket,msg,strlen(msg),MSG_NOSIGNAL) == -1) return false;
if(send(socket,"\n",1,MSG_NOSIGNAL) == -1) return false;
}
bool readFrom(int socket,char*buffer)
{
memset(buffer,0,SIZEBUFFER);
#ifdef WIN32
if((recv(socket, buffer, SIZEBUFFER-1, 0)) <=0 ) return false;
#else
if(read(socket,buffer,SIZEBUFFER-1) == -1) return false;
#endif
}
void 
stopClient(int * socket)
{
close(*socket);
}


