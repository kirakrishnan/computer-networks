/**********************************************************************
CSCI 631    Assignment 3            2015
Programmer: ARAVINDA KRISHNAN V
Section:    0002
Date Due:   03/19/2015
Purpose:    Wrapper functions for client and server to handle errors in system calls socket(), inet_pton(), connect(),
            fputs(), close(),  writen(), Fork(),fgets(),Signal(), readline()     
*********************************************************************/

#include "wrapper3.h"

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

int Fputs( const char *str , FILE *stream )
{
        errno = 0 ;
        int i;
        if( ( i = fputs( str , stream ) ) == EOF )
        {
            fprintf( stderr , " fputs failed\t:\t%s\n" , strerror( errno ) );
            exit( 6 );
        }
        return i;
}

int Fork()
{
        errno=0;
        int n=fork();
        if(n<0)
             perror("Unable to create child process");
        return n;
}


int Close( int fd )
{
        errno = 0 ;
        int i;
        if( ( i = close( fd ) ) == -1 )
        {
            fprintf( stderr , " Error in closing\t:\t%s\n", strerror( errno ) );      
		    exit( 7 );
        }
        return i;
}


ssize_t Writen( int fd , const void *buf , size_t n )
{
	errno = 0 ;
	ssize_t i ;
	if( ( i = writen( fd , buf , n ) ) == -1 )
	{
		fprintf( stderr , "Writen error\t:\t%s\n" , strerror( errno ) );	
		exit( 13 );
	}
	return i;
}


ssize_t Readline( int fd , void *buf , size_t n )
{
	errno = 0 ;
	ssize_t i ;
	if( ( i = readline( fd , buf , n ) ) == -1 )
	{
		fprintf( stderr , " Readline error\t:\t%s\n" , strerror( errno ));
		exit( 14 );
	}
	return i ;
}

char *Fgets( char *string , int size , FILE *stream )
{
	errno = 0 ;
	char *i = fgets( string , size , stream ) ;
	return i ;
}

int Accept( int sockfd , struct sockaddr *addr , socklen_t *addrlen )
{
	errno = 0 ;
	int i ;
	if( ( i = accept( sockfd , addr , addrlen ) ) == -1 )
	{
		fprintf( stderr , "Accept error\t:\t%s\n" , strerror( errno ) );
		Close( sockfd );
		exit( 16 );
	}
	return i;
}

int Bind( int sockfd , const struct sockaddr *addr , socklen_t addrlen )
{
	errno = 0 ;	
	int i ;
	if( ( i = bind( sockfd , addr , addrlen ) ) == -1 )
	{
		fprintf( stderr , "Bind error\t:\t%s\n" , strerror( errno ) );
		Close( sockfd );
		exit( 17 );
	}
	return i;
}


int Listen( int sockfd , int backlog )
{
        errno = 0 ;
        int i ;
        if( ( i = listen( sockfd , backlog ) ) == -1 )
        {
                fprintf( stderr , "Listen error\t:\t%s\n" , strerror( errno ) );
                Close( sockfd );
                exit( 18 );
        }
        return i;
}


FILE *Fopen( const char *path , const char *mode )
{
        errno = 0 ;
        FILE *fp = fopen( path , mode );
        if( errno != 0 )
        {
                fprintf( stderr , "Fopen error\t:\t%s\n" , strerror( errno ) );
                exit( 20 );
        }
        return fp;
}


int Fclose( FILE *fp )
{
        errno = 0 ;
        int i = fclose( fp ) ;
        if( errno != 0 )
        {
                fprintf( stderr , "Bind error\t:\t%s\n" , strerror( errno ) );
                exit( 21 );
        }
        return i;
}


int Fseek( FILE *stream , long int offset , int origin )
{
        errno = 0 ;
        int i ;
        if( ( i = fseek( stream , offset , origin ) ) != 0 )
        {
                fprintf( stderr , "Fseek error\t:\t%s\n" , strerror( errno ) );
                exit( 24 );
        }
        return i;
}

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



