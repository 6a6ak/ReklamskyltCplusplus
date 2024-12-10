#ifndef CUSTOMERS_H
#define CUSTOMERS_H

constexpr int MaxMessageLength = 50;
constexpr int MaxMessages = 3;

class Customer
{
private:
    char name[MaxMessageLength];
    int payment;
    char messages[MaxMessages][MaxMessageLength];
    int messageCount;

public:
    Customer(const char *customerName, int customerPayment, const char customerMessages[][MaxMessageLength], int messageCount);

    const char *getName() const;
    int getPayment() const;
    int getMessageCount() const;
    const char *getMessage(int index) const;
    const char *getRandomMessage() const;
    int getDisplayWeight() const;
};

#endif
