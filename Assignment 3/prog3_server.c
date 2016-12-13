/**********************************************************************
CSCI 631    Assignment 3            2015
Programmer: ARAVINDA KRISHNAN V
Section:    0002
Date Due:   03/19/2015
Purpose :   This program takestakes book name as input and displays respective              Authorname.  And it displays  when a child is terminated.
*********************************************************************/

#include "prog3_server.h"

int main ( int argc, char* argv [ ] )
{	
   	int listenfd , connfd;			//initialize the file descriptors
	struct sockaddr_in cliaddr,servaddr;    	
   	int port_no;			//initialize port number
   	FILE *fp;
        pid_t childpid;
        socklen_t clilen;
        void sig_chld(int);
 	int i = argc ;
   	if( i == 1 )
      port_no = SERV_PORT;
     	
	else if( i == 2 )
      port_no = atoi( argv[ 1 ] );
	
	if ( argc > 2 ) 
	{
       	fprintf ( stderr, "usage: %s [ port-number ]\n",argv [ 0 ] );
		exit ( 1 );
    }
	
    fp = Fopen( a , "r" );				//Opening file 'a' as readable   
    listenfd = Socket ( AF_INET, SOCK_STREAM, 0 );		//Calling the Socket function it creates internet stream
  	bzero ( &servaddr, sizeof ( servaddr ) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
    servaddr.sin_port = htons( port_no );
    Bind( listenfd , ( SA* ) &servaddr , sizeof ( servaddr ) );		//Binding the socket to network address	
    Listen( listenfd , LISTENQ );			//Establishing queue for listening requests
    Signal(SIGCHLD,sig_chld);
   	while ( true )     
	{
        clilen=sizeof(cliaddr);
        if((connfd= Accept(listenfd,(struct sockaddr *) &cliaddr,&clilen))<0)			// Statement to accept the clients
          {
           if(errno==EINTR)
             continue;
           else
             perror("accept error");
          }

        if((childpid=fork())==0)
          {
           close(listenfd);	
           str_echo( connfd, fp );		
           exit ( 0 );
    }
   	Close ( connfd );
}
}

void str_echo ( int sockfd, FILE *fp )
{
    	ssize_t n;		
    	int rsize;
    	char book [ MAXLINE ], author[ MAXLINE ];	
	
	while ( true ) 
	{
        	if ( ( n = Readline ( sockfd, book, MAXLINE ) ) == 0 ) 		//Reading the book name from socket
      		return;
		
		bzero( author ,  sizeof( author ) );	
		rsize = book_auth( fp, book , author ); 		//gets Function to get name of socket
		Writen ( sockfd, author, rsize );				//Writing into socket author name
    }	
}
void sig_chld(int signo)
{ 
         pid_t pid;
         int stat;
         while(signo)
         break;
         while((pid=waitpid(-1,&stat,WNOHANG))>0)
         fprintf(stdout,"child %d terminated \n",pid);
         return;
}
int book_auth(FILE *fp, char key[], char result[])
{
    	char book[ 100 ], author[ 100 ]; 	
    	int r;
    
	Fseek(fp , 0 , SEEK_SET );	//Calling the Fseek function to get to beginning of file

    	while(true)    
	    {
        	fscanf( fp ,"%[^:]s" , book );		
        	fscanf( fp , ":" );       
        	fscanf(fp,"%[^:]s", author);
        	fscanf(fp,":\n");        		
       		strcat(book,"\n");	//Concatenating the escape character
        	if(strcasecmp(book,key) ==0)        //Comparing the book and key array
		{
            		strcpy(result, author);
            		strcat(result,"\n");
			        r = strlen(result);		
            		return r;
        } 
        	if(feof(fp))
      		break;
    }
    strcpy(result, "unknown\n");	//Unknown if no match found
	r = strlen(result);
	return r;
}

