#include "customers.h"
#include "random.h" // Include for pseudoRandom()
#include <string.h> // Use C-style string header

Customer::Customer(const char *customerName, int customerPayment, const char customerMessages[][50], int messageCount)
{
    if (!customerName) customerName = "";
    if (!customerMessages) messageCount = 0;

    strncpy(name, customerName, 49);
    name[49] = '\0';

    payment = customerPayment;
    this->messageCount = messageCount > 3 ? 3 : messageCount;

    for (int i = 0; i < this->messageCount; ++i)
    {
        strncpy(messages[i], customerMessages[i], 49);
        messages[i][49] = '\0';
    }
}

const char *Customer::getName() const
{
    return name;
}

int Customer::getPayment() const
{
    return payment;
}

int Customer::getMessageCount() const
{
    return messageCount;
}

const char *Customer::getMessage(int index) const
{
    if (index < 0 || index >= messageCount)
        return nullptr;
    return messages[index];
}

const char *Customer::getRandomMessage() const
{
    if (messageCount <= 0)
        return nullptr;
    int randomIndex = pseudoRandom() % messageCount;
    return getMessage(randomIndex);
}

int Customer::getDisplayWeight() const
{
    return payment / 100;
}
