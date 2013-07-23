/* 
 * File:   SocketControl.h
 * Author: merma
 *
 * Created on July 19, 2013, 12:51 AM
 */

#ifndef SOCKETCONTROL_H
#define	SOCKETCONTROL_H

#define PORT 9513

using namespace std;

class SocketControl {
public:
    SocketControl();
    SocketControl(const SocketControl& orig);
    virtual ~SocketControl();
    bool open();
    bool conectar();
    string leer();
    bool escribir(string s);
    void desconectar();
    void cerrar();
private:
    int sockfd,newsockfd,n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

};

#endif	/* SOCKETCONTROL_H */

