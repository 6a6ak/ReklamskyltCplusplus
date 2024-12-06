#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "utilities.h"  // Include utilities.h for pseudoRandom()

class Customer {
private:
    const char* name;
    int payment;
    const char (*messages)[50];
    int messageCount;

public:
    Customer(const char* name, int payment, const char (*messages)[50], int messageCount)
        : name(name), payment(payment), messages(messages), messageCount(messageCount) {}

    const char* getName() const {
        return name;
    }

    int getPayment() const {
        return payment;
    }

    int getMessageCount() const {
        return messageCount;
    }

    const char* getMessage(int index) const {
        if (index >= 0 && index < messageCount) {
            return messages[index];
        }
        return nullptr;
    }

    const char* getRandomMessage() const {
        int randomIndex = pseudoRandom() % messageCount; // Use pseudoRandom()
        return getMessage(randomIndex);
    }

    int getDisplayWeight() const {
        return payment / 1000;
    }
};

#endif
