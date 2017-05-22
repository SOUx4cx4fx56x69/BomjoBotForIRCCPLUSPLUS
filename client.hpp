int 
InitClient(const char*host,int portno);
bool
writeTo(int socket,char*msg);
bool readFrom(int socket,char*buffer);
void 
stopClient(int * socket);
void _closed_(int);
void _open_now_(void);
bool _is_connected(void);
//bool is_connect(int socket);
