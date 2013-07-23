/* 
 * File:   Hilos.h
 * Author: merma
 *
 * Created on July 19, 2013, 2:39 AM
 */

#ifndef HILOS_H
#define  HILOS_H

class Hilos {
public:
    Hilos();
    Hilos(const Hilos& orig);
    virtual ~Hilos();
    static void *run(void *me);
private:
    pthread_t h1;
};

#endif	/* HILOS_H */

