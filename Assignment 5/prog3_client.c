/**********************************************************************
assignment number : 3
Programmer: Nitin kotcherlakota
course/Section:   CSCI 631/0002
Date Due:  03/19/2015
Purpose:  Client requests author name by giving Title of the book as an input
  since the client is connected to the 
*********************************************************************/

#include "prog3_client.h"
int main ( int argc, char* argv [ ] )
{
   int sockfd;
//	int i;
//	double n=0.00;
	char in_buf[MAXLINE];
	struct sockaddr_in servaddr;
	struct hostent *hp;
//	char author[MAXLINE];
	if (argc!=3)
	{

   		 usage("Invalid arguments");
	}
	sockfd=Socket(AF_INET,SOCK_STREAM,0);//create a socket
	memset(&servaddr,0,sizeof(servaddr));//zero-out 
	servaddr.sin_family=AF_INET;//set address family 
	const char* s1=argv[1];
	hp = gethostbyname(s1);
	bcopy( hp->h_addr, &(servaddr.sin_addr.s_addr), hp->h_length);
	servaddr.sin_port=htons(atoi(argv[2]));
//	w_inet_pton(AF_INET,argv[1],&servaddr.sin_addr);//convert the IP address from ASCII to numeric format
	Connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));//connect to the server

	printf("Enter Sequence:");
	while(w_fgets(in_buf, sizeof(in_buf), stdin)!=NULL)
	{
//		printf("'%s'",in_buf);
	//	w_fputs("Sum of exponents:",stdout);
		/* i=strlen(in_buf)-1;
                while(i>=0 && isspace(in_buf[i])){//remove \n character
                        in_buf[i]='\0';
                        i--;
                }*/
		trim(in_buf);
	//	doQuery(sockfd,in_buf);//client function call
		//printf("'%s'\n",author);
//		n=n+atof(author);
//		 w_fputs("Boo:",stdout);
		 //  int i;
	writen(sockfd, in_buf, strlen(in_buf));
//	if(strcmp(title,"\n"))	
		writen(sockfd,"\n",1);
/*	authorlen=readline(sock, author, authorlen);
	 i=strlen(author)-1;
        while(i>0 && isspace(author[i])){//removing spaces and new line carriage returns
                author[i]='\0';
                --i;
        }*/
//	return(authorlen);
	
		}
//		sleep(4);
//	printf("yey");
	shutdown(sockfd,SHUT_WR);
//	printf("done");
	char st[MAXLINE];
	
//	while(readline(sockfd,st,MAXLINE)!=0);
	readline(sockfd,st,MAXLINE);
//	printf("'%s'",st);
	trim(st);
	/* i=strlen(st)-1;
	printf("length %d",i);
                while(i>=0 && isspace(st)){//remove \n character
                        st[i]='\0';
                        i--;
                }
		 printf("'%s'",st);

		printf("heere is %s",st);
	printf("sum of exponents:%f",atof(st));
	*/
//	shutdown(sockfd,SHUT_WR);
	  printf("sum of exponents:'%s'",st);

	Close(sockfd); //close socket

	exit(0);
}

// function execution

/*void snd_rcv ( FILE* fp, int sockfd )
{
	char senddata [ MAXLINE ], recvdata [ MAXLINE ];   // character declarations used for sending and receiving data
        printf("\t\n\n*************BOOKNAME AND ITS AUTHORS*************\n\n");
	printf("\n\tEnter the book name\t:\t");    //prompts to enter the book name
	while ( Fgets ( senddata, MAXLINE, fp ) ) 	//Retrieving author name from server
    	{        	
        Writen( sockfd , senddata , strlen( senddata ) ); 		//Calling wrapper function of writen     
        Readline ( sockfd , recvdata , MAXLINE ); 		//Calling wrapper function of readline
        printf("\t\tAuthor name\t:\t");         //prints author name
        Fputs ( recvdata, stdout );        //prints data onto stdout that is, screen
	printf("\n\tEnter the book name\t:\t");   
        }
    	printf("\n");    // new line
}*/


