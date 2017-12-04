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

    for(unsigned long a = 0; a < length; a++){
        cout << "a: " << a << " digits[a]: " << digits[a] << endl;
    }   
}

BigInt::BigInt(const BigInt &b)
    :isNegative(b.isNegative), length(b.length), digits(new unsigned short[b.length])
{
    cout << "#----- copy constructor -----#" << endl;
    for(unsigned long i = 0; i < this->length; i++){
        this->digits[i] =b.digits[i];
    }
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

BigInt::~BigInt(){
    cout << "#----- deconstructor -----#" << endl;
    delete[] digits;
    digits = nullptr;
} 

//BigInt(const BigInt &bi); //copy constructor
//BigInt& operator = (const BigInt &bi); //assignment operator
