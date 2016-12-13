/**********************************************************************
CSCI 631    Assignment 2            2015
Programmer: ARAVINDA KRISHNAN V
Section:    0002
Date Due:   02/25/2015
Purpose:    It gives the author names of given books
************************************************************************/

#include "wrapper2.h"

#define a "/home/631/common/books.d" // Defining Variable 'a' to the given file path

#ifndef SERVER_H
#define SERVER_H
	
	void str_echo( int sockfd , FILE *fp );                        
	int book_auth( FILE *filep , char book[] , char author[ ] );
	
#endif


