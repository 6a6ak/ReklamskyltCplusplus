#include "customers.h"
#include <string.h> // For strncpy
#include <stdlib.h> // For rand()

Customer::Customer(const char* name, int payment, const char msgArray[][50], int msgCount)
    : payment(payment), messageCount(msgCount) {
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0'; // Ensure null termination

    for (int i = 0; i < msgCount && i < MAX_MESSAGES; ++i) {
        strncpy(this->messages[i], msgArray[i], sizeof(this->messages[i]) - 1);
        this->messages[i][sizeof(this->messages[i]) - 1] = '\0'; // Ensure null termination
    }
}

const char* Customer::getName() const {
    return name;
}

int Customer::getPayment() const {
    return payment;
}

const char* Customer::getRandomMessage() const {
    if (messageCount == 0) return "No messages available.";
    int index = rand() % messageCount;
    return messages[index];
}
