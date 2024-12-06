#include "Costumer.h"
#include <string.h>

Costumer::Costumer(char *message1, char *message2, char *message3)

{
    strcpy(this->messages[0], message1);
    strcpy(this->messages[1], message2);
    strcpy(this->messages[2], message3);
}

char* Costumer::GetMessage(int i) {
    if (i >= 0 && i < 3) {
        return messages[i];
    }
    return "";
}
