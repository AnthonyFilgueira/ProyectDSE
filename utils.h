/* 
 * File:   utils.h
 * Author: merma
 *
 * Created on July 22, 2013, 9:14 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <time.h>
using namespace std;

class utils {
public:
    utils();
    utils(const utils& orig);
    virtual ~utils();
    static string strtoupper(string str);
    static string strtolower(string str);
    static string parserIn(int number);
    static int getRandNumber(int ini, int fin);
private:

};

#endif	/* UTILS_H */

