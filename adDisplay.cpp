#include <cstdlib>
#include <ctime>
#include <cstring>
#include "AdDisplay.h"

int chooseCustomer(Customer customers[], int customerCount, int lastCustomer) {
    int chosenCustomer;
    do {
        chosenCustomer = rand() % customerCount;
    } while (chosenCustomer == lastCustomer);
    return chosenCustomer;
}

void showAd(Customer* customer) {
    for (int i = 0; i < 3; i++) {
        if (strlen(customer->messages[i]) > 0) {
            lcdWriteText(customer->messages[i]);
        }
    }
}

void lcdWriteText(const char* text) {
    
}
