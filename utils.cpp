/* 
 * File:   utils.cpp
 * Author: merma
 * 
 * Created on July 22, 2013, 9:14 PM
 */

#include "utils.h"

using namespace std;

utils::utils() {}

utils::utils(const utils& orig) {}

utils::~utils() {}

string utils::strtoupper(string str){
    int leng=str.length();
    for(int i=0; i<leng; i++)
        if (97<=str[i]&&str[i]<=122)//a-z
            str[i]-=32;
    return str;
}
string utils::strtolower(string str){
    int leng=str.length();
    for(int i=0; i<leng; i++)
        if (65<=str[i]&&str[i]<=90)//A-Z
            str[i]+=32;
    return str;
}
string utils::parserIn(int number){
    ostringstream postr;
    postr << number;
    return postr.str();
}

int utils::getRandNumber(int ini, int fin){
    srand(time(NULL));               
    return ini+rand()%((fin+1)-ini);
}