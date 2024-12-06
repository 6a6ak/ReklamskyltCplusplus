#ifndef CUSTOMERS_H_
#define CUSTOMERS_H_

#define MAX_MESSAGES 5

class Customer {
private:
    char name[50];
    int payment;
    char messages[MAX_MESSAGES][50];
    int messageCount;

public:
    Customer(const char* name, int payment, const char msgArray[][50], int msgCount);

    const char* getName() const;
    int getPayment() const;
    const char* getRandomMessage() const;
};

#endif // CUSTOMERS_H_
