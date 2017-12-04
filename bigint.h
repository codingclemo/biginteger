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
    BigInt(const BigInt &b); //copy constructor

    short cmp(const BigInt &b) const; //compare

    bool operator == (const BigInt &b) const;
    bool operator != (const BigInt &b) const { return !operator == (b); }
    bool operator < (const BigInt &b) const;
    bool operator <= (const BigInt &b) const;
    bool operator > (const BigInt &b) const;
    bool operator >= (const BigInt &b) const;

    friend std::ostream &operator << (std::ostream &output, const BigInt &b);


    //BigInt& operator = (const BigInt &bi); //assignment operator
};



#endif