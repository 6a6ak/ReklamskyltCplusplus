#include "Costumer.h"
#include <string.h>

Costumer::Costumer(char *companyname, char *message1, char *message2, char *message3, int pay)
{
    strcpy(this->companyname, companyname);
    strcpy(this->messages[0], message1);
    strcpy(this->messages[1], message2);
    strcpy(this->messages[2], message3);
    this->pay = pay;
}

char* Costumer::GetCompanyName() {
    return companyname;
}

char* Costumer::GetMessage(int index) {
    if (index >= 0 && index < 3) {
        return messages[index];
    }
    return "";
}

int Costumer::GetPay(){
    return pay;
}
