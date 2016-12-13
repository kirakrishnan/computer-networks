#include "/home/courses/631/common/631.h"
#ifndef H_wrapper
#define H_wrapper

	// binds the socket file discriptor to the server address
	int Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
	
	//listens to the socket till an request arrives
	int Listen(int sockfd, int backlog);
	
	//accepts the connection from the client
	int Accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
	
	//write the buf to the file discriptor
	ssize_t Write(int fd, const void* buf, size_t count);
	
	//gets the time 
	time_t Time(time_t * t);
	
	//creates a file with end to end connection
	int Socket(int domain,int type,int protocol);
	
	// closes the fle discriptor
	int Close(int fd);
        
        //client wrapper prototypes
        //function to connect to a server
        int Connect(int sockfd,const struct sockaddr* addr, socklen_t addrlen);

        //function to close a file
        int Close(int fd);

        //function to read from a file
        ssize_t Read(int fd,void*buf, size_t count);

        //function to write to the stream
        int Fputs(const char* s,FILE* stream);

        //function to convert presentation to network addressing
        int Inet_pton(int af,const char * src ,void* dst);

        //function to create a socket file
        int Socket(int domain,int type,int protocol);

#endif