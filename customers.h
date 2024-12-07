#ifndef CUSTOMERS_H
#define CUSTOMERS_H

class Customer {
private:
    char name[50]; // Name is now mutable, stored as a character array
    int payment;   // Payment amount
    char messages[3][50]; // Array of customer messages
    int messageCount;     // Number of messages

public:
    // Constructor
    Customer(const char* customerName, int customerPayment, const char customerMessages[][50], int messageCount);

    // Getters
    const char* getName() const;
    int getPayment() const;
    int getMessageCount() const;
    const char* getMessage(int index) const;
    const char* getRandomMessage() const;
    int getDisplayWeight() const;
};

#endif
