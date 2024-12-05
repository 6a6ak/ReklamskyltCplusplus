#include "Costumer.h"
#include <string.h>

// Constructor
Costumer::Costumer(const char *companyname, const char *message1, const char *message2, const char *message3, int pay)
{
    strcpy(this->companyname, companyname);
    strcpy(this->message1, message1);
    strcpy(this->message2, message2);
    strcpy(this->message3, message3);
    this->pay = pay;
}

// Getter methods
const char* Costumer::getCompanyName() const {
    return companyname;
}

const char* Costumer::getMessage1() const {
    return message1;
}

const char* Costumer::getMessage2() const {
    return message2;
}

const char* Costumer::getMessage3() const {
    return message3;
}

int Costumer::getPay() const {
    return pay;
}

// Setter methods
void Costumer::setCompanyName(const char* companyname) {
    strcpy(this->companyname, companyname);
}

void Costumer::setMessage1(const char* message1) {
    strcpy(this->message1, message1);
}

void Costumer::setMessage2(const char* message2) {
    strcpy(this->message2, message2);
}

void Costumer::setMessage3(const char* message3) {
    strcpy(this->message3, message3);
}

void Costumer::setPay(int pay) {
    this->pay = pay;
}
