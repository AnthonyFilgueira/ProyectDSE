/* 
 * File:   UsbControl.cpp
 * Author: merma
 * 
 * Created on July 14, 2013, 6:33 PM
 */

#include <iostream>
#include <usb.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "UsbControl.h"

using namespace std;

UsbControl::UsbControl() {}

UsbControl::UsbControl(const UsbControl& orig) {}

UsbControl::~UsbControl() {}

void UsbControl::begin(){    
    out = inicializar_picusb();
}
/*
 * device_init()
 * FUNCION que busca el device file que corresponda con el Vendor ID
 * y el IdProduct de nuestro dispositivo
 * @return: estructura del dispositivo (descriptor)
 */
struct usb_device * UsbControl::device_init(void){
    struct usb_bus *usb_bus, *usb_busses;    
    struct usb_device *dev;
		
    usb_init();
    usb_find_busses();
    usb_find_devices();
    usb_busses = usb_get_busses();

    for (usb_bus = usb_busses;usb_bus;usb_bus = usb_bus->next){
        for (dev = usb_bus->devices;dev;dev = dev->next){				  
                  if ((dev->descriptor.idVendor== FTDI_VID) && (dev->descriptor.idProduct== FTDI_PDT)){                      
                      setPermissions(usb_bus->dirname,usb_bus->devices->filename);					  
		      return dev;
		  }
       	}
    }
    return NULL;
}
/* 
 * setPermissions()
 * PROCEDIMIENTO que ejecuta linea de comando nativo del sistema 
 * con el objetivo de asignar permisos de lectura y escritura al
 * device file que corresponde al dispositivo (Hardware)
 * @bus: indica el bus por el que esta conectado el dispositivo
 * @dev: indica el device file correspondiente al dispositivo
 * 
 */
void UsbControl::setPermissions(char* bus, char* dev){
    char path[254] = "echo jut120388 | sudo -S chmod 0777 /dev/bus/usb";
        strcat(path,"/");  strcat(path,bus);
	strcat(path,"/");  strcat(path,dev);				
	system(path);        
}
int UsbControl::inicializar_picusb(){
    usb_dev = device_init();   

    if (usb_dev == NULL){
	//fprintf(stderr, "Dispositivo no encontrado. - %d (%s)\n", errno, strerror(errno));        
        return -1;
     }
    
    usb_handle = usb_open(usb_dev);
    
    if (usb_handle == NULL){
	//fprintf(stderr, "No logra abrir usb port. - %d (%s)\n", errno, strerror(errno));        
        return -2;
    }
    return 0;
}
bool UsbControl::write_usb(){
    if (!out){
        //buffer de lectura y escritura
        char cmd[4];
        cmd[0] = 'd';            

        if (usb_bulk_write(usb_handle,0x01,cmd,4,2000)<0)             
            return false;
        return true;
    }
    return false;
}
string UsbControl::read_usb(){
    if (!out){
        //buffer de lectura y escritura
        char cmd[4];
        char buffer[50];
        int a,b,c;
        string salida;
        
        if (usb_bulk_read(usb_handle,0x81,cmd,4,100000)<0)
            fprintf(stderr, "No logra leer de usb port. - %d (%s)\n", errno, strerror(errno));					
        
        a = (int) cmd[0];
        b = (int) cmd[1];
        c = (int) cmd[2];
        
        snprintf(buffer,50,"%d-%d.%d",a,b,c);
        salida.append(buffer);
        fflush(stdout);
        return salida;
    }
    return "Default";
}