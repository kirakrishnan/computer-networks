/**********************************************************************
assignment number : 3
Programmer: Nitin kotcherlakota
course/Section:   CSCI 631/0002
Date Due:  03/19/2015
Purpose: Wrapper functions for all system calls     
*********************************************************************/

#include "wrapper3.h"

//fork function

int Fork()
{
errno=0;
int n=fork();
if(n<0)
perror("unable to create child process");
return n;
}

//wrapper function for signal system call
Sigfunc * Signal(int signo, Sigfunc *func)
{
    struct sigaction act,oact;
    act.sa_handler=func;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(signo==SIGALRM)
    {
        #ifdef SA_INTERRUPT
                act.sa_flags |=SA_INTERRUPT;
        #endif
    }
    else
    {
        #ifdef SA_RESTART
                act.sa_flags |=SA_RESTART;
        #endif
    }
    if(sigaction(signo, &act, &oact)<0)
        return (SIG_ERR);
    return(oact.sa_handler);
}

 //wrapper function for socket system call. 

int Socket( int domain , int type , int protocol )
{
        errno = 0 ;
        int sockfd;
        if( ( sockfd = socket( domain , type , protocol ) ) == -1 )
        {
            fprintf( stderr , " Socket error\t:\t%s\n" , strerror( errno ) );     
		    exit( 1 );
        }
        return sockfd;
}

//wrapper function for Inet_pton system call.

int Inet_pton( int domain , const char *source , void *destination )
{
        errno = 0 ;
        int i;
        i = inet_pton( domain , source , destination );
        if( i == -1 )
        {
            fprintf( stderr , "INET_PTON (return value -1 ) Error\t:\t%s\n" , strerror( errno ) );
            exit( 2 );
        }

        else if( i == 0 )
        {
                fprintf( stderr , "INET_PTON error with return value %d\n" , i );
                exit( 3 );
        }
        return i;
}

//wrapper function for connect system call.

int Connect( int sockfd , const struct sockaddr *server , socklen_t addrlen )
{
        errno = 0 ;
        int i;
        if( (i = connect( sockfd , server , addrlen ) ) == -1 )
        {
                perror("Connect Error\n");
		Close( sockfd );
		exit( 4 );
        }
        return i;
}

//wrapper function for Fputs system call.

int Fputs( const char *str , FILE *stream )
{
        errno = 0 ;
        int i;
        if( ( i = fputs( str , stream ) ) == EOF )
        {
            fprintf( stderr , " fputs failed\t:\t%s\n" , strerror( errno ) );
            exit( 8 );
        }
        return i;
}

//wrapper function for close system call.

int Close( int fd )
{
        errno = 0 ;
        int i;
        if( ( i = close( fd ) ) == -1 )
        {
            fprintf( stderr , " Error in closing\t:\t%s\n", strerror( errno ) );      
		    exit( 5 );
        }
        return i;
}

//wrapper function for writeln system call.

ssize_t Writen( int fd , const void *buf , size_t n )
{
	errno = 0 ;
	ssize_t i ;
	if( ( i = writen( fd , buf , n ) ) == -1 )
	{
		fprintf( stderr , "Writen error\t:\t%s\n" , strerror( errno ) );	
		exit( 15 );
	}
	return i;
}

//wrapper function for readline system call.

ssize_t Readline( int fd , void *buf , size_t n )
{
	errno = 0 ;
	ssize_t i ;
	if( ( i = readline( fd , buf , n ) ) == -1 )
	{
		fprintf( stderr , " Readline error\t:\t%s\n" , strerror( errno ));
		exit( 12 );
	}
	return i ;
}

//wrapper function for fgets system call.

char *Fgets( char *string , int size , FILE *stream )
{
	errno=0;
    char* t;
    if ((t=(fgets(string,size,stream))) == NULL && errno!=0) 
    {
        fprintf(stderr,"fgets error at client\n"); 
        exit(1);
    }
    return t;
}
//wrapper function for accept system call.

int Accept( int sockfd , struct sockaddr *addr , socklen_t *addrlen )
{
	errno = 0 ;
	int i ;
	if( ( i = accept( sockfd , addr , addrlen ) ) == -1 )
	{
		fprintf( stderr , "Accept error\t:\t%s\n" , strerror( errno ) );
		Close( sockfd );
		exit( 14 );
	}
	return i;
}

//wrapper function for bind system call.

int Bind( int sockfd , const struct sockaddr *addr , socklen_t addrlen )
{
	errno = 0 ;	
	int i ;
	if( ( i = bind( sockfd , addr , addrlen ) ) == -1 )
	{
		fprintf( stderr , "Bind error\t:\t%s\n" , strerror( errno ) );
		Close( sockfd );
		exit( 15 );
	}
	return i;
}

//wrapper function for listen system call.
int Listen( int sockfd , int backlog )
{
        errno = 0 ;
        int i ;
        if( ( i = listen( sockfd , backlog ) ) == -1 )
        {
                fprintf( stderr , "Listen error\t:\t%s\n" , strerror( errno ) );
                Close( sockfd );
                exit( 14 );
        }
        return i;
}

//wrapper function for fopen system call.

FILE *Fopen( const char *path , const char *mode )
{
        errno = 0 ;
        FILE *fp = fopen( path , mode );
        if( errno != 0 )
        {
                fprintf( stderr , "Fopen error\t:\t%s\n" , strerror( errno ) );
                exit( 10 );
        }
        return fp;
}

//wrapper function for fclose system call.

int Fclose( FILE *fp )
{
        errno = 0 ;
        int i = fclose( fp ) ;
        if( errno != 0 )
        {
                fprintf( stderr , "Bind error\t:\t%s\n" , strerror( errno ) );
                exit( 19 );
        }
        return i;
}

//wrapper function for fseek system call.


int Fseek( FILE *stream , long int offset , int origin )
{
        errno = 0 ;
        int i ;
        if( ( i = fseek( stream , offset , origin ) ) != 0 )
        {
                fprintf( stderr , "Fseek error\t:\t%s\n" , strerror( errno ) );
                exit( 26 );
        }
        return i;
}

void trim(char* str){
int i=strlen(str)-1;
                while(i>=0 && isspace(str[i])){//remove \n character
                        str[i]='\0';
                        i--;
                }

}





