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
        // cout << "  i: " << i << " digit: " << digits[i] << " value: " << value << endl;
        value = value / 10;
    }
}

BigInt::BigInt(unsigned short int arrayOfDigits[], unsigned long arrayLength)
    :isNegative(false), length(0), digits(nullptr)
{
    cout << "#----- constructor short array -----#" << endl;

    //get real length
    for(unsigned long i = 0; i < arrayLength; i++){
        if(arrayOfDigits[i] > 9){
            unsigned short helpValue = arrayOfDigits[i];
            while(helpValue != 0){
                cout << "helpvalue: " << helpValue << endl;
                helpValue = helpValue / 10;
                length++;
            }
        } else {
            length++;
        }
    }
    
    //allocate memory with real length 
    digits = new unsigned short [length];

    cout << "arrayLength: " << arrayLength << endl;
    cout << "length: " << length << endl;
    
    unsigned long arrayIndex = 0;

    for(unsigned long i = 0; i < arrayLength; i++){
        if(arrayOfDigits[i] > 9){
            unsigned short helpValue = arrayOfDigits[i];
            unsigned short helpArray[] = {0,0,0,0,0};
            unsigned short helpLength = 0;
            int j = 0;
            while(helpValue != 0){
                helpArray[j] = helpValue % 10;
                helpValue = helpValue / 10;
                helpLength++;
                j++;
            }

            for(unsigned short k = 0; (k < helpLength) && (helpLength-k-1 >= 0); k++){
                digits[arrayIndex] = helpArray[helpLength -k -1];
                arrayIndex++;
            }
        } else {
            digits[arrayIndex] = arrayOfDigits[i];
            arrayIndex++;
        }
    }
    /*
    for(unsigned long a = 0; a < length; a++){
        cout << "a: " << a << " digits[a]: " << digits[a] << endl;
    } */  
}

BigInt::~BigInt(){
    cout << "#----- deconstructor -----#" << endl;
    delete[] digits;
    digits = nullptr;
} 

BigInt::BigInt(const BigInt &b)
    :isNegative(b.isNegative), length(b.length), digits(new unsigned short[b.length])
{
    cout << "#----- copy constructor -----#" << endl;
    for(unsigned long i = 0; i < this->length; i++){
        this->digits[i] =b.digits[i];
    }
}

BigInt& BigInt::operator = (const BigInt &b) {
    cout << "#----- assignment operator -----#" << endl;
    if (this != &b) {
        isNegative = b.isNegative;
        length = b.length;
        digits = new unsigned short[length];

        for(unsigned long i = 0; i < length; i++){
            digits[i] = b.digits[i];
        }
    }
    return *this;
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
              //  cout << "i: " << i << " this.digits[i]: " << this->digits[i] << "\tb.digits[i]: " << b.digits[i] << endl;
            while(this->digits[i] == b.digits[i] && i < this->length-1){
                i++;
              //  cout << "i: " << i << " this.digits[i]: " << this->digits[i] << "\tb.digits[i]: " << b.digits[i] << endl;
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

bool BigInt::operator == (const BigInt &b) const{
    bool equal = 0 == cmp(b);
    return equal;
}
bool BigInt::operator < (const BigInt &b) const{
    bool equal = -1 == cmp(b);
    return equal;
}
bool BigInt::operator <= (const BigInt &b) const{
    bool equal = (-1 == cmp(b) || (0 == cmp(b)));
    return equal;       
}
bool BigInt::operator > (const BigInt &b) const{
    bool equal = 1 == cmp(b);
    return equal;
}
bool BigInt::operator >= (const BigInt &b) const{
    bool equal = (1 == cmp(b) || (0 == cmp(b)));
    return equal;    
}

ostream &operator << (std::ostream &output, const BigInt &b) {
    if (b.isNegative) {
        output << "-";
    }
    for (unsigned long i = 0; i < b.length; i++) {
        output << b.digits[i];
    }
    return output;
}


BigInt operator + (const BigInt &a, const BigInt &b) {
    cout << "#----- + operator -----#" << endl;
    unsigned long newLength = max(a.length, b.length);

    unsigned short newArray[newLength];
    cout << "newLength: " << newLength << endl;

    //make arrays of BigInt same sized
    unsigned short diff = newLength - a.length;
    unsigned short helpA[newLength];
    for(unsigned long i = 0; i < diff; i++){
        helpA[i] = 0;
    }
    for(unsigned long i = diff; i < a.length; i++){
        helpA[i] = a.digits[i];
    }

    diff = newLength - b.length;
    unsigned short helpB[newLength];
    for(unsigned long i = 0; i < diff; i++){
        helpB[i] = 0;
    }
    for(unsigned long i = diff; i < b.length; i++){
        helpB[i] = b.digits[i];
    }

    unsigned short sum = 0;
    unsigned short rest = 0;
    unsigned short carry = 0;

    for(unsigned long i = newLength -1; i != 0; i--){
            sum = a.digits[i] + b.digits[i] + carry;
            if(sum > 9){
                carry = 1;
                rest = sum % 10;
            } else {
                carry = 0;
                rest = sum;
            }
           // cout << "i: " << i;
           // cout << " a.digits[i]: " << a.digits[i] << " b.digits[i]: " << b.digits[i];
           // cout << " sum: " << sum << " rest: " << rest << " carry: " << carry;

            newArray[i] = rest;
           // cout << " newArray[i]: " << newArray[i] << endl;
    }
    cout << "a: |";
    for(unsigned long i = 0; i < a.length; i++){
        cout <<  a.digits[i] << "|";
    }
    cout << endl;

    cout << "b: |";
    for(unsigned long i = 0; i < b.length; i++){
        cout <<  b.digits[i] << "|";
    }
    cout << endl;
 
    BigInt n(newArray, newLength);

    cout << "n: |";
    for(unsigned long i = 0; i < n.length; i++){
        cout <<  n.digits[i] << "|";
    }
    cout << endl;

    return n;
}
