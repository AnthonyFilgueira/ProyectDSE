/* 
 * File:   UsbControl.h
 * Author: merma
 *
 * Created on July 14, 2013, 6:33 PM
 */

#ifndef USBCONTROL_H
#define	USBCONTROL_H

#define FTDI_VID   0x04d8 /* Vendor  Id */
#define FTDI_PDT   0x0011 /* Product Id */

#include <iostream>
using namespace std;

class UsbControl {
public:
    UsbControl();
    UsbControl(const UsbControl& orig);
    virtual ~UsbControl();
    void begin();
    void setPermissions(char *bus,char *dev);
    struct usb_device *device_init(void);    
    int inicializar_picusb();
    bool write_usb();
    string read_usb();
private:
    struct usb_dev_handle *usb_handle;
    struct usb_device     *usb_dev;
    int out;

};

#endif	/* USBCONTROL_H */

