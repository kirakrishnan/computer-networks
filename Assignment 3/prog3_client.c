/**********************************************************************
CSCI 631 	Assignment 3		 2015
Programmer: ARAVINDA KRISHNAN V
Section:    0002
Date Due:   03/19/2015
Purpose:    Client enters the title of the book and requests author name.
*********************************************************************/

#include "prog3_client.h"

int main ( int argc, char* argv [ ] )
{
   	int sockfd, port_no;			//initializing socket fd and port number
   	struct sockaddr_in servaddr;	
    	
	if( argc == 2 )    // error condition
	{
        	port_no = SERV_PORT;	
    }
	else if ( argc == 3 )
	{
        	port_no = atoi(argv[2]);	//converts string to integer
   	}	
    else    
	{
        	fprintf ( stderr, "usage: %s server-address [port-number]\n", argv [ 0 ] ); // prints if no of arguments is zero 
        	exit ( 10 );
    }  	
	sockfd = Socket ( AF_INET, SOCK_STREAM, 0 );  	 //Calling the Socket function it creates internet stream    	
	bzero ( &servaddr, sizeof ( servaddr ) );		//Clearing the Socket structure
	servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons ( port_no );
	Inet_pton ( AF_INET, argv[1], &servaddr.sin_addr ); //Converting the socket address to network readable form
	Connect ( sockfd, ( SA* ) &servaddr, sizeof ( servaddr ) );  //calling the connect wrapper function to establish connection
	send_recv ( stdin, sockfd );
	Close ( sockfd );
	return 0;
}
// function execution
void send_recv ( FILE* fp, int sockfd )
{
	char senddata [ MAXLINE ], recvdata [ MAXLINE ];
	printf("\n\tEnter the book name\t:\t");
	while ( Fgets ( senddata, MAXLINE, fp ) ) 	//Retrieving author name from server
    	{        	
        Writen( sockfd , senddata , strlen( senddata ) ); 		
		printf("%s\t ", senddata);
        Readline ( sockfd , recvdata , MAXLINE );
        printf("\tAuthor name\t\t:\t");
        Fputs ( recvdata, stdout );
		printf("\n\n\tEnter the book name\t:\t");
	    }
    	printf("\n");
}


