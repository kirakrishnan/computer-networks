/**********************************************************************
CSCI 631    Assignment 2            2015
Programmer: ARAVINDA KRISHNAN V
Section:    0002
Date Due:   02/25/2015
Purpose:    wrapper function declarations.   
*********************************************************************/


#include "/home/631/common/631.h"
#include "/home/631/common/in_out.h"

#ifndef WRAPPER2_H
#define WRAPPER2_H
	
    int Socket( int domain , int type , int protocol );                             

    int Inet_pton( int domain , const char *source , void *destination);            

    int Connect( int sockfd , const struct sockaddr* server , socklen_t addrlen );  

    ssize_t Readline( int fd , void *buf , size_t n );                              

    int Fputs( const char *str , FILE *stream );	                                

    int Close( int sockfd );                                                        

    ssize_t Writen( int fd , const void *buf , size_t n );    	                

	char *Fgets( char *string , int size , FILE *stream );  			

	int Accept( int sockfd , struct sockaddr *addr , socklen_t *addrlen );	

	int Bind( int sockfd , const struct sockaddr *addr , socklen_t addrlen );

	int Listen( int sockfd , int backlog );						

	FILE *Fopen( const char *path , const char *mode );			

	int Fclose( FILE *fp );
	
	int Fseek( FILE *stream , long int offset , int origin );
	
	
#endif


