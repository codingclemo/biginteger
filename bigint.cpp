#include <ostream>
#include "bigint.h"

using namespace std;

BigInt::BigInt(long value)
    :isNegative(false), length(0), digits(nullptr)
{
    //cout << "#----- constructor long -----#" << endl;
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
    //cout << "#----- constructor short array -----#" << endl;

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
}

BigInt::~BigInt(){
    //cout << "#----- deconstructor -----#" << endl;
    delete[] digits;
    digits = nullptr;
} 

BigInt::BigInt(const BigInt &b)
    :isNegative(b.isNegative), length(b.length), digits(new unsigned short[b.length])
{
    //cout << "#----- copy constructor -----#" << endl;
    for(unsigned long i = 0; i < this->length; i++){
        this->digits[i] =b.digits[i];
    }
}

BigInt& BigInt::operator = (const BigInt &b) {
    //cout << "#----- assignment operator -----#" << endl;
    if (this != &b) {
        isNegative = b.isNegative;
        length = b.length;

        // irgendwo  in einem der beiden/dreien konstruktoren gab es schon ein new -> zuerst ein delete
        delete[] digits; 
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
    //cout << "#----- + operator -----#" << endl;

    // die länge kann, muss aber nicht, um 1 größer sein
    // zB.:  9 + 9 = 18     max(a.length, b.length ) = 1 
    // newLnegth muss aber 2 sein - das macht dir dann unten probleme beim while (vormals for)
    unsigned long newLength = max(a.length, b.length);

    unsigned short newArray[newLength];
    //cout << "newLength: " << newLength << endl;

    //make arrays of BigInt same sized
    unsigned short diff = newLength - a.length;
    unsigned short helpA[newLength];
    for(unsigned long i = 0; i < diff; i++){
        helpA[i] = 0;
    }
    for(unsigned long i = diff; i < newLength; i++){
        helpA[i] = a.digits[i-diff];
    }

    diff = newLength - b.length;

    unsigned short helpB[newLength];
    for(unsigned long i = 0; i < diff; i++){
        helpB[i] = 0;
    }
    for(unsigned long i = diff; i < newLength; i++){
        helpB[i] = b.digits[i-diff];
    }

    unsigned short sum = 0;
    unsigned short rest = 0;
    unsigned short carry = 0;

    // das for/while funktioniert nur gut, wenn beide Zahlen gleich viele Digits haben
    // und das ergbenis auch nur soviele digits
    // zB 99 + 99 geht so nicht

    unsigned long i = newLength -1;
    // mit der for loop und der abbruchbedingung i != 0 hast du nie i = 0 bearbeitet, deswegen
    // hat die 1. stelle gefehlt
    while(i >= 0) {
            sum = helpA[i] + helpB[i] + carry;
            if(sum > 9){
                carry = sum / 10;
                rest = sum % 10;
            } else {
                carry = 0;
                rest = sum;
            }
            /* cout << "i: " << i;
            * cout << " a.digits[i]: " << a.digits[i] << " b.digits[i]: " << b.digits[i];
            * cout << " sum: " << sum << " rest: " << rest << " carry: " << carry;
            */
            newArray[i] = rest;
            //cout << " newArray[i]: " << newArray[i] << endl;

            // wenn i == 0 ist und dann kommt das i--, dann wird i irgendneinen POSITIVEN wert annehmen
            // deswegen das break   vor dem i--
            if (i == 0) break;
            i--; 
    }
    unsigned short adaptedArray[newLength+1];
    if (carry){
        //cout << "-- carry --" << endl;
        newLength++;
        adaptedArray[0] = carry;
        for(unsigned long i = 1; i < newLength; i++){
            adaptedArray[i] = newArray[i-1];
        }
    }

    BigInt n(newArray, newLength);
    BigInt na(adaptedArray, newLength);

    if(carry){
        return na;
    } else {
        return n;
    }
}

BigInt operator - (const BigInt &a, const BigInt &b) {
    //cout << "#----- - operator -----#" << endl;
    BigInt newA = a;
    BigInt newB = b;
    bool swapped = false;
    // make newA the larger value for easier procedure;
    if(a.cmp(b) < 0){
        newA = b;
        newB = a;
        swapped = true;
    }
    unsigned long newLength = max(newA.length, newB.length);
    unsigned short newArray[newLength];
    //make arrays of BigInt same sized
    unsigned short diff = newLength - newA.length;
    unsigned short helpA[newLength];
    for(unsigned long i = 0; i < diff; i++) { helpA[i] = 0; }
    for(unsigned long i = diff; i < newLength; i++) { helpA[i] = newA.digits[i-diff]; }

    diff = newLength - newB.length;
    unsigned short helpB[newLength];
    for(unsigned long i = 0; i < diff; i++) { helpB[i] = 0; }
    for(unsigned long i = diff; i < newLength; i++) { helpB[i] = newB.digits[i-diff]; }

    unsigned short minuend = 0;
    unsigned short subtrahend = 0;
    unsigned short carry = 0;    
    for (unsigned long i = newLength - 1; i >= 0; i--){
        minuend = helpA[i] + carry * 10;
        subtrahend = helpB[i] + carry;
        //set carry
        if(helpA[i] < helpB[i]){
            carry = 1;
        } else { 
            carry = 0; 
        }
        newArray[i] = minuend - subtrahend;
        //cout << i << ". " << newArray[i] << " = " << minuend << " - " << subtrahend << "//" << "carry: " << carry << endl;
        
        if(i == 0) break;
    }
    //get rid of zeros at the beginning of the array
    unsigned long adaptedLength = newLength;
    for(unsigned long i = 0; i < newLength;i++){
        if(newArray[0] == 0){
            while(newArray[i] == 0){
                //cout << i << ". newArray[i]: " << newArray[i] << endl;
                adaptedLength--;
            }
        }
        //cout << i << ". newArray[i]: " << newArray[i] << endl;
    }

    unsigned short adaptedArray[adaptedLength];
    unsigned long diffLength = newLength - adaptedLength;
    for(unsigned long i = diffLength; i < newLength; i++){
        adaptedArray[i-diffLength] = newArray[i];
        //cout << i << ". adaptedArray[i]: " << adaptedArray[i] << endl;
    }
    
    BigInt n(adaptedArray, adaptedLength);
    n.isNegative = swapped;
    //n.length = adaptedLength;
    //n.digits = adaptedArray;

    return n;
}