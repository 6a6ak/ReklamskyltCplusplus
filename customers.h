#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "utilities.h"

class Customer {
private:
    const char* name;
    int payment;
    char messages[3][50]; // Remove `const` here to allow initialization in the constructor
    int messageCount;

public:
    Customer(const char* name, int payment, const char messages[][50], int messageCount);

    const char* getName() const;
    int getPayment() const;
    int getMessageCount() const;
    const char* getMessage(int index) const;
    const char* getRandomMessage() const;
    int getDisplayWeight() const;
};

#endif
