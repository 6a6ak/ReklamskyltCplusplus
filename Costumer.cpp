#include "Costumer.h"
#include <string.h>

Costumer::Costumer(char *companyname, char *message1, char *message2, char *message3, int ay)
{
    strcpy(this->companyname, companyname);
    strcpy(this->message1, message1);
    strcpy(this->message2, message2);
    strcpy(this->message3, message3);
    this->pay = pay;
}
