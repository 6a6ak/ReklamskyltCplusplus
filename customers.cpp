#include "customers.h"
#include "random.h" // Include for pseudoRandom()

// Constructor definition
Customer::Customer(const char *customerName, int customerPayment, const char customerMessages[][50], int messageCount)
{
    // Copy the customer name
    int i, j;
    for (i = 0; customerName[i] != '\0' && i < 49; ++i)
    {
        name[i] = customerName[i];
    }
    name[i] = '\0'; // Null-terminate the name

    // Set payment and message count
    payment = customerPayment;
    this->messageCount = messageCount > 3 ? 3 : messageCount; // Limit messages to max 3

    // Copy each message into the internal array
    for (i = 0; i < this->messageCount; ++i)
    {
        for (j = 0; j < 50; ++j)
        {
            messages[i][j] = customerMessages[i][j];
            if (customerMessages[i][j] == '\0')
                break;
        }
        messages[i][49] = '\0'; // Null-terminate each message
    }
}

// Getter for name
const char *Customer::getName() const
{
    return name;
}

// Getter for payment
int Customer::getPayment() const
{
    return payment;
}

// Getter for message count
int Customer::getMessageCount() const
{
    return messageCount;
}

// Getter for a specific message by index
const char *Customer::getMessage(int index) const
{
    return (index >= 0 && index < messageCount) ? messages[index] : nullptr;
}

// Get a random message
const char *Customer::getRandomMessage() const
{
    int randomIndex = pseudoRandom() % messageCount; // Get a random index from 0 to messageCount - 1 (inclusive) using pseudoRandom() from utilities.h
    return getMessage(randomIndex);
}

// Calculate display weight based on payment
int Customer::getDisplayWeight() const
{
    return payment / 100;
}
