#include "prog4_udpclient.h"
int main ( int argc, char* argv [ ] )
{
   	int sockfd, port_no;			//initializing socket fd and port number
   	struct sockaddr_in servaddr;		//structure for addresses
    	
if( argc == 2 )    // condition check
	{
        	port_no = SERV_PORT;	//if no port number then default port number is set
    }
	else if ( argc == 3 )  //condition check
	{
        	port_no = atoi(argv[2]);  //if port given then port is set
   	}	
    else    
	{
		//print if no arguments
        	fprintf ( stderr, "usage: %s server-address [port-number]\n", argv [ 0 ] ); 
        	exit ( 10 );
    }  	
	
if(argc !=2)
perror("error in udp");   	
	bzero ( &servaddr, sizeof ( servaddr ) );		//Initializing the Socket structure to zero
	servaddr.sin_family = AF_INET;              //Ipv4 is set
    servaddr.sin_port = htons ( port_no );   
	Inet_pton ( AF_INET, argv[1], &servaddr.sin_addr ); //Converting the socket address to network readable form
	//Connect ( sockfd, ( SA* ) &servaddr, sizeof ( servaddr ) );  //Establishing a connection to the given ip address
	//snd_rcv ( stdin, sockfd );	//Calling function to send to server and recieve from server
	sockfd = Socket ( AF_INET, SOCK_STREAM, 0 );  	 //Calling the wrapper Socket function
	dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));
	exit(0);  //closes socket file descriptor
}
// function execution
/*
void snd_rcv ( FILE* fp, int sockfd )
{
	char senddata [ MAXLINE ], recvdata [ MAXLINE ];   // character declarations used for sending and receiving data
	printf("\n\tEnter the book name\t:\t");    //prompts to enter the book name
	while ( Fgets ( senddata, MAXLINE, fp ) ) 	//Retrieving author name from server
    	{        	
        Writen( sockfd , senddata , strlen( senddata ) ); 		//Calling wrapper function of writen
		printf("%s\t ", senddata);       
        Readline ( sockfd , recvdata , MAXLINE ); 		//Calling wrapper function of readline
        printf("\tAuthor name\t\t:\t");         //prints author name
        Fputs ( recvdata, stdout );        //prints data onto stdout that is, screen
		printf("\n\n\tEnter the book name\t:\t");   
	    }
    	printf("\n");    // new line
}
*/
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int n;
	char sendline [MAXLINE], recvline[MAXLINE + 1];
	while(Fgets(sendline, MAXLINE, fp)!=NULL)
	{
		sendto(sockfd,sendline,strlen(sendline), 0, pservaddr, servlen);
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		recvline[n]=0;
		Fputs(recvline, stdout);
	}
}
