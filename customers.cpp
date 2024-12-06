#include "customers.h"

// Constructor definition
Customer::Customer(const char* name, int payment, const char messages[][50], int messageCount)
    : name(name), payment(payment), messageCount(messageCount) {
    for (int i = 0; i < messageCount && i < 3; ++i) {
        // Copy strings manually
        for (int j = 0; j < 50; ++j) {
            this->messages[i][j] = messages[i][j];
            if (messages[i][j] == '\0') break; // Stop copying at null terminator
        }
        this->messages[i][49] = '\0'; // Ensure null termination
    }
}

const char* Customer::getName() const {
    return name;
}

int Customer::getPayment() const {
    return payment;
}

int Customer::getMessageCount() const {
    return messageCount;
}

const char* Customer::getMessage(int index) const {
    return (index >= 0 && index < messageCount) ? messages[index] : nullptr;
}

const char* Customer::getRandomMessage() const {
    int randomIndex = pseudoRandom() % messageCount;
    return getMessage(randomIndex);
}

int Customer::getDisplayWeight() const {
    return payment / 1000;
}
