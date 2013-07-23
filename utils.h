/* 
 * File:   utils.h
 * Author: merma
 *
 * Created on July 22, 2013, 9:14 PM
 */

#ifndef UTILS_H
#define	UTILS_H

using namespace std;

class utils {
public:
    utils();
    utils(const utils& orig);
    virtual ~utils();
    static string strtoupper(string str);
    static string strtolower(string str);
private:

};

#endif	/* UTILS_H */

