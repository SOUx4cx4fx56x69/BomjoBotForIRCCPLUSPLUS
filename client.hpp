int 
InitClient(const char*host,int portno);
bool
writeTo(int socket,char*msg);
bool readFrom(int socket,char*buffer);
void 
stopClient(int * socket);
//bool is_connect(int socket);
