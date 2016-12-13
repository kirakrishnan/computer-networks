/**********************************************************************
CSCI 631    Assignment 2            2015
Programmer: ARAVINDA KRISHNAN V
Section:    0002
Date Due:   02/25/2015
Purpose:    This program finds the name of the author for the given book name.
*********************************************************************/

#include "prog2_server.h"

int main ( int argc, char* argv [ ] )
{	
   	int listenfd , connfd;			//initialize the file descriptors
	struct sockaddr_in servaddr;    	
   	int port_no;			//initialize port number
   	FILE *fp;
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

   	while ( true )     
	{
		connfd= Accept(listenfd,(struct sockaddr *) NULL,NULL);			// Statement to accept the clients
     	str_echo( connfd, fp );		
        Close ( connfd ); 
		exit ( 0 );
    }
   	Close ( listenfd );
    exit ( 0 );
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

