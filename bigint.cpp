#include <ostream>
#include "bigint.h"

using namespace std;

/* Variables 
private:
    bool isNegative;
    unsigned long length;
    unsigned short *digits;
*/


BigInt::BigInt(long value)
    :isNegative(false), length(0), digits(nullptr)
{
    cout << "#----- constructor long -----#" << endl;
    //check sign
    isNegative = value < 0;
    if(isNegative){ value *= -1; }
    //get length
    long valueCopy = value;
    while(valueCopy != 0){
        valueCopy = valueCopy / 10;
        length++;
    }
    //allocate memory
    digits = new unsigned short[length];
    //store digits
    for(int i = length -1; i >= 0; i--){
        digits[i] = value % 10;
        cout << "  i: " << i << " digit: " << digits[i] << " value: " << value << endl;
        value = value / 10;
    }
}

BigInt::BigInt(unsigned short *arrayOfDigits)
    :isNegative(false), length(0), digits(nullptr)
{
    cout << "#----- constructor short array -----#" << endl;
    //TODO 1
}

short BigInt::cmp(const BigInt &b) const
{
    short returnVal = 0;

    if(this->isNegative != b.isNegative){
        if(this->isNegative){
            returnVal = -1;
        } else {
            returnVal = 1;
        }
    } else {
        if(this->length == b.length){
            int i = 0;
                cout << "i: " << i << " this.digits[i]: " << this->digits[i] << "\tb.digits[i]: " << b.digits[i] << endl;
            while(this->digits[i] == b.digits[i] && i < this->length-1){
                i++;
                cout << "i: " << i << " this.digits[i]: " << this->digits[i] << "\tb.digits[i]: " << b.digits[i] << endl;
            }
            
            if(this->digits[i] > b.digits[i]){ 
                returnVal = 1;
            } else if (this->digits[i] < b.digits[i]){
                returnVal = -1;
            } else {
                returnVal = 0;
            }       
        } else if(this->length < b.length) {
            returnVal = -1;
        } else {
            returnVal = 1;
        }

        if (this->isNegative){
            returnVal *= -1;
        }
    }
    cout << "returnVal: " << returnVal << endl;
    return returnVal;
}

BigInt::~BigInt(){
    cout << "#----- deconstructor -----#" << endl;
    delete[] digits;
    digits = nullptr;
} 

//BigInt(const BigInt &bi); //copy constructor
//BigInt& operator = (const BigInt &bi); //assignment operator
