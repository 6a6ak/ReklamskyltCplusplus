#ifndef AD_DISPLAY_H
#define AD_DISPLAY_H

#include <string>

#define MAX_CUSTOMERS 5

struct Customer {
    char name[50];
    int amountPaid;
    char messages[3][100];
};

int chooseCustomer(Customer customers[], int customerCount, int lastCustomer);
void showAd(Customer* customer);
void lcdWriteText(const char* text);

#endif
