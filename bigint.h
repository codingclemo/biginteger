#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include "bigint.h"

class BigInt {
/* Variables */
private:
    bool isNegative;
    unsigned long length;
    unsigned short *digits;

/* Methods */
public:
    explicit BigInt(long value = 0); //constructor
    explicit BigInt(unsigned short *arrayOfDigits); //constructor
    virtual ~BigInt(); //destructor

    short cmp(const BigInt &b) const; //compare

    //BigInt(const BigInt &bi); //copy constructor

    //BigInt& operator = (const BigInt &bi); //assignment operator
};



#endif