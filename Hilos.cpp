/* 
 * File:   Hilos.cpp
 * Author: merma
 * 
 * Created on July 19, 2013, 2:39 AM
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "UsbControl.h"
#include "SocketControl.h"
#include "utils.h"
#include "Hilos.h"

using namespace std;

UsbControl    driver;
SocketControl socketx;

pthread_mutex_t mutexBuffer;

int sw0 = 1;
string cmd, in;

Hilos::Hilos() {
    driver.begin();    
    
    if (socketx.open()){    
        pthread_mutex_init (&mutexBuffer, NULL);
        pthread_create (&h1 , NULL , run , NULL);
        pthread_join(h1,NULL);
    }
    printf ( "Fin \n");
}

Hilos::Hilos(const Hilos& orig) {}

Hilos::~Hilos() {}

void * Hilos::run(void *me){
    int bandera = 1;
    pthread_mutex_lock (&mutexBuffer);
    
    if (socketx.conectar()){
        while(sw0){            
           cmd = socketx.leer();
           cmd = utils::strtolower(cmd);
           
           if (cmd.compare(0,3,"out") == 0){ 
               cout << "Saliendo" << endl;
               break;
           }
           
           /* Comandos */
           if (cmd.compare(0,10,"practica_1") == 0){
               
               if (!driver.write_usb()){
                   driver.begin();
                   driver.write_usb();
               }
               
               in = driver.read_usb();
               socketx.escribir(in);
               cout << in << endl;
               bandera = 0;
           }
           if (bandera)
                socketx.escribir("default");
        }
        socketx.desconectar();
        socketx.cerrar();
    }
    pthread_mutex_unlock (&mutexBuffer);
    
    return NULL;    
}