/* 
 * File:   SocketControl.cpp
 * Author: merma
 * 
 * Created on July 19, 2013, 12:51 AM
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "SocketControl.h"

using namespace std;

SocketControl::SocketControl() {}

SocketControl::SocketControl(const SocketControl& orig) {}

SocketControl::~SocketControl() {}

bool SocketControl::open(){
     sockfd = socket(AF_INET, SOCK_STREAM, 6);
     if (sockfd < 0) 
         return false;
     
     /* Agregar Opciones */
     struct timeval timeout;      
     timeout.tv_sec = 10;
     timeout.tv_usec = 0;
     int flag;
     
     flag = 1;
     if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
         return false;

     if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
         return false;
	 
     if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR,&flag, sizeof flag) < 0)
	 return false;
         
     bzero((char *) &serv_addr, sizeof(serv_addr));
     
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);
     return true;
}

bool SocketControl::conectar(){
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	return false;
    return true;
}

string SocketControl::leer(){
    string salida;
    listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     
     if (newsockfd < 0)          
         return "ERROR ACCEPT"; 
     
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) 
         return "ERROR LEER";
     
     salida.append(buffer);
     return salida;
}

bool SocketControl::escribir(string s){        
    const char *cc = s.c_str();
    strcpy(buffer,cc);
    n = write(newsockfd,buffer,s.length());
    if (n < 0)
        return false;
    return true;
}

void SocketControl::desconectar(){
    close(newsockfd);
}

void SocketControl::cerrar(){    
    shutdown(sockfd,SHUT_RDWR);
    close(sockfd);    
}