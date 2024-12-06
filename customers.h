#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <stdlib.h> // Use C-style stdlib.h for rand()

class Customer {
private:
    const char* name;
    int payment;               // Customer's payment amount
    const char (*messages)[50]; // Array of customer messages
    int messageCount;          // Number of messages

public:
    // Constructor
    Customer(const char* name, int payment, const char (*messages)[50], int messageCount)
        : name(name), payment(payment), messages(messages), messageCount(messageCount) {}

    // Getter for customer name
    const char* getName() const {
        return name;
    }

    // Getter for customer payment
    int getPayment() const {
        return payment;
    }

    // Getter for message count
    int getMessageCount() const {
        return messageCount;
    }

    // Getter for a specific message by index
    const char* getMessage(int index) const {
        if (index >= 0 && index < messageCount) {
            return messages[index];
        }
        return nullptr; // Return null if index is invalid
    }

    // Function to get a random message
    const char* getRandomMessage() const {
        int randomIndex = rand() % messageCount;
        return getMessage(randomIndex);
    }

    // Function to calculate display weight
    int getDisplayWeight() const {
        return payment / 1000; // Weight proportional to payment
    }
};

#endif
