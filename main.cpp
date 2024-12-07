#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 
#include "lcd.h"
#include "uart.h"

#define MAX_CUSTOMERS 5

struct Customer {
    char name[50];
    int amountPaid;
    char messages[3][100];
};

int chooseCustomer(Customer customers[], int customerCount, int lastCustomer);
void showAd(HD44780& lcd, Customer* customer);

int main(void) {
    init_serial();
    HD44780 lcd;
    lcd.Initialize(); 
    lcd.Clear();      

    srand(time(0)); 

    Customer customers[MAX_CUSTOMERS] = {
        {"Hederlige Harrys Bilar", 1500, {"Köp bil hos Harry", "En god bilaffär (för Harry!)", "Hederlige Harrys Bilar"}},
        {"Farmor Ankas Pajer AB", 3000, {"Köp paj hos Farmor Anka", "Skynda innan Mårten ätit alla pajer"}},
        {"Svarte Petters Svartbyggen", 1500, {"Låt Petter bygga åt dig", "Bygga svart? Ring Petter"}},
        {"Långbens Detektivbyrå", 4000, {"Mysterier? Ring Långben", "Långben fixar biffen"}},
        {"IOT:s Reklambyrå", 1000, {"Synas här? IOT:s Reklambyrå"}}
    };

    int customerCount = MAX_CUSTOMERS;
    int lastCustomer = -1;

    lcd.WriteText((char *)"Reklamskylt startar...");
    _delay_ms(2000); 

    while (true) {
        int chosenCustomer = chooseCustomer(customers, customerCount, lastCustomer);
        if (chosenCustomer != -1) {
            showAd(lcd, &customers[chosenCustomer]);
            lastCustomer = chosenCustomer;
        }
        _delay_ms(20000); 
    }

    return 0;
}

int chooseCustomer(Customer customers[], int customerCount, int lastCustomer) {
    int chosenCustomer;
    do {
        chosenCustomer = rand() % customerCount;
    } while (chosenCustomer == lastCustomer);
    return chosenCustomer;
}

void showAd(HD44780& lcd, Customer* customer) {
    lcd.Clear();
    for (int i = 0; i < 3; i++) {
        if (strlen(customer->messages[i]) > 0) {
            lcd.WriteText((char *)customer->messages[i]);
            _delay_ms(5000); 
            lcd.Clear();
        }
    }
}
