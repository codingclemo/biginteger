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
    explicit BigInt(unsigned short int arrayOfDigits[], unsigned long arrayLength); //constructor
    virtual ~BigInt(); //destructor
    BigInt(const BigInt &b); //copy constructor
    BigInt& operator = (const BigInt &b); //assignment operator

    short cmp(const BigInt &b) const; //compare
    
    /* bool operations */
    bool operator == (const BigInt &b) const;
    bool operator != (const BigInt &b) const { return !operator == (b); }
    bool operator < (const BigInt &b) const;
    bool operator <= (const BigInt &b) const;
    bool operator > (const BigInt &b) const;
    bool operator >= (const BigInt &b) const;

    friend std::ostream &operator << (std::ostream &output, const BigInt &b);

    /* artimetic functions */
    friend BigInt operator + (const BigInt &a, const BigInt &b);

};

#endif