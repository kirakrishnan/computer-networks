#include "wrapper.h"

int Close(int fd)
{
	int i; //used to catch the return value of close function
	errno = 0;//resetting the errno

	i = close(fd);

	if ( i < 0 )	{ perror("close error"); exit(1);}
	return i;
}

//Creates an endpoint for communication and returns descriptor
int Socket(int domain,int type,int protocol)
{
	int socfd;//used to get the socket file discriptor if the socket function is succesful
 
	errno = 0;//resetting the errno

	socfd = socket(domain,type,protocol);

	if (socfd < 0)
	{
	perror("socket error");
	exit(2);
	}
	return socfd;
}

//Current time in seconds
time_t Time(time_t * t)
{
	errno = 0;//resetting the errno
	
	time_t t1;//to get the time in seconds

	if((t1 = time(t)) < 0)
	{
	perror("can't get time");
	exit(3);
	}
	return t1;
}

// write to the file with file discriptor buffer and size as input
ssize_t Write(int fd, const void* buf, size_t count)
{
	ssize_t i;//to get the number of bytes written in the file

	errno = 0;//resetting errno

	i = write(fd,buf,count);

	if(i < 0)
	{
	perror("write error");
	exit(4);
	}
	return i;
}

// accepts the connection from the client
int Accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen)
{
	int accp;//to get the connection file discriptor

	errno = 0;//resetting errno

	accp = accept(sockfd,addr,addrlen);

	if( accp < 0)
	{
	perror("accept error");
	exit(5);
	}
	return accp;
}

//binds the file discriptor of socket to the server address
int Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen)
{
	int i;//to get the return value of bind function

	errno = 0;//resetting the errno

	i = bind(sockfd,addr,addrlen);

	if(i < 0)
	{
	perror("bind failed");

	exit(6);
	}
	return i;
}

//the server listens to the socket till an request comes
int Listen(int sockfd, int backlog)
{
	int i;//to get the return value of listen function

	errno = 0;//resetting the errno

	i = listen(sockfd,backlog);

	if(i < 0)
	{

	perror("listen failed");

	exit(7);
	}
	return i;
}

//Cleint wrapper functions
//connects to the socket with file discriptor sockfd with address addr and address length as addrlen
int Connect(int sockfd,const struct sockaddr* addr, socklen_t addrlen)
{
	int i;//return value of connect function

	errno = 0;//setting the errno to 0

	i = connect(sockfd,addr, addrlen);

	if ( i < 0 ) { perror("connect error"); exit(1); }

	return i;
}

//reads from file fd into buffer buf with size count
ssize_t Read(int fd,void*buf, size_t count)
{
	ssize_t i;//return value of read function 
	errno = 0;//setting the errno to 0

	i = read(fd,buf,count);

	if( i < 0 ){ perror("read error"); exit(3);}

	return i;
}

//writes to stream
int Fputs(const char* s,FILE * stream)
{
	int i;//return value for fputs function

	errno = 0;//setting errno to 0
	
	i = fputs(s,stream);

	if(i == EOF){ perror("fputs error"); exit(4); }

	return i;

}

//converts presentation into network address structure
int Inet_pton(int af,const char * src ,void* dst)
{

	int i;//return value for inet_pton function
	
	errno = 0;//setting errno to 0
	
	i=inet_pton(af,src,dst);
	
	if(i == 0 ){  fprintf(stderr,"inet_pton error: Invalid address\n");  exit(5);}
	
	else if(i < 0){  perror("inet_pton error");   exit(6);}

	return i;
}