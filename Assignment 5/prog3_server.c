/**********************************************************************
assignment number : 3
Programmer: Nitin kotcherlakota
course/Section:   CSCI 631/0002
Date Due:  03/19/2015
Purpose: Concurrent Server allows multiple clients to run in the foreground while 
 it is running in the background.
*********************************************************************/

#include "prog3_server.h"

//function for sig child
void sig_chld(int signo)
  {
   pid_t pid;
   int stat;
    if(signo) 
    {}
    while((pid=waitpid(-1,&stat,WNOHANG))>0)
        fprintf(stdout,"child %d terminated \n",pid);
    return;
  } 

//main function 
int main ( int argc, char* argv [ ] )
{	
   	int listenfd , connfd;			//initialize the file descriptors
	struct sockaddr_in cliaddr, servaddr;    	//structure of addresses
   	int port_no;			//initialize port number
   	FILE *fp;    				//file pointer	
	pid_t childpid;
        socklen_t clilen;
        void sig_chld(int);

//check for errors in user programs
   	int i = argc ;
   	if( i == 1 )
        port_no = SERV_PORT;   //if no port number then default port number is set
	else if( i == 2 )
        port_no = atoi( argv[ 1 ] );    //if port given then port is set
	if ( argc > 2 ) 
	{
       	fprintf ( stderr, "usage: %s [ port-number ]\n",argv [ 0 ] );
	exit ( 1 );
        }
        fp = Fopen( a , "r" );				//Opening file 'a' in read mode   
        listenfd = Socket ( AF_INET, SOCK_STREAM, 0 );		//Calling the wrapper Socket function
        bzero ( &servaddr, sizeof ( servaddr ) );   //initializing socket addresses to zero
        servaddr.sin_family = AF_INET; //Ipv4 is set
        servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
        servaddr.sin_port = htons( port_no );
        Bind( listenfd , ( SA* ) &servaddr , sizeof ( servaddr ) );		//Binds the socket to network address	
        Listen( listenfd , LISTENQ );			//Establishing queue for listening requests
        Signal(SIGCHLD, sig_chld);
    
//looping   
 while ( true )     
	{
        clilen=sizeof(cliaddr);
	if((connfd= Accept(listenfd,(struct sockaddr *) &cliaddr,&clilen))<0)	// Statement to accept the clients
         {
        if(errno==EINTR)           // checks for interrupt
           continue;
        else
           perror("accept errot");
         }
        if((childpid=Fork())==0)    //forking
        {
          close(listenfd);
          str_echo( connfd);	//calling the str_echo function in this child to deal with client
          exit ( 0 );
        }
   	Close ( connfd );  //closes the listening file descriptor
   }
}
//str_echo function declaration

void str_echo ( int sock)
{
 //	char author[MAXLINE],title[MAXLINE];
//	char unknown[]="unknown";
	double  i=0.00;
	double k=0.0;
	char a[MAXLINE];
	int n=0;
//	int x=0;
        while(readline(sock,a,MAXLINE+1)>0){
			n++;
		
/*		if(readline(sock,a,MAXLINE+1)==0)
			return;*/
		printf("'%s'",a);
		trim(a);
	       /* x=strlen(a)-1;
		while(x>=0 && isspace(a[x])){//remove newline
			a[x]='\0';
			x--;	
		}*/
		 printf("'%s'",a);

//		const char* st=a;
		if(n==1){
			
			k=strtod(a,NULL);
			continue;
			}
/*	FILE *fp;
        fp=w_fopen(bookdb, "r");
		while(1){
  			if( fscanf(fp, " %[^:]:%[^:]:", title, author)==EOF){//match for pattern
                          writen(sock,unknown,strlen(unknown));//write to socket "unknown"
                          writen(sock,"\n",1);//write new line
                          break;
		}
		if(!strcasecmp(a,title)){//matching title
                        writen(sock,author,strlen(author));//writing authorname to socket
			writen(sock,"\n",1);//send a new line
                          break;	
		}
				
		}
	fclose(fp);//close file*/
//		frg();
//		const char* p=a;
		double a1=strtod(a,NULL);
		 printf("'%f'",a1);

		i=i+pow(a1,k);
//		i=i+a1;
		 printf("'%f'",i);

	}
	sprintf(a,"%f",i);
	printf("this is '%s'",a);
//	strcat(a,"\n");
	writen(sock,a,strlen(a));
	writen(sock,"\n",1);//send a new line	
}


