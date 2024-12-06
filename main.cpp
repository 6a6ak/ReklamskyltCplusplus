#include "lcd.h"
#include "customers.h"
#include "uart.h"
#include "utilities.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Custom delay function
void custom_delay_ms(int delayMs) {
    while (delayMs > 0) {
        if (delayMs >= 10) {
            _delay_ms(10);
            delayMs -= 10;
        } else {
            _delay_ms(1);
            delayMs--;
        }
    }
}

// Function to select a customer based on weight
Customer* selectCustomer(Customer* customers, int customerCount, Customer* lastCustomer) {
    int totalWeight = 0;

    // Calculate total weight
    for (int i = 0; i < customerCount; ++i) {
        totalWeight += customers[i].getDisplayWeight();
    }

    Customer* selectedCustomer = nullptr;
    while (selectedCustomer == nullptr || selectedCustomer == lastCustomer) {
        int randomWeight = pseudoRandom() % totalWeight;
        for (int i = 0; i < customerCount; ++i) {
            randomWeight -= customers[i].getDisplayWeight();
            if (randomWeight < 0) {
                selectedCustomer = &customers[i];
                break;
            }
        }
    }

    return selectedCustomer;
}

int main(void) {
    // Seed the random number generator dynamically
    randomSeed = TCNT1; // Use Timer1 as seed

    // Initialize the LCD
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();

    // Initialize UART for debugging
    init_serial();
    printf("UART Initialized. Starting program...\n");

    // Define customers
    const char harryMessages[][50] = {
        "Buy a car from Harry!",
        "A good deal (for Harry!)",
        "Honest Harry's Cars"
    };
    const char ankaMessages[][50] = {
        "Buy pies from Anka!",
        "Hurry, before they are gone!"
    };
    const char petterMessages[][50] = {
        "Let Petter build for you!",
        "Building black? Call Petter!"
    };
    const char nackademinMessages[][50] = {
        "   NackademiN"
    };

    Customer customers[] = {
        Customer("Harry", 5000, harryMessages, 3),
        Customer("Anka", 3000, ankaMessages, 2),
        Customer("Petter", 1500, petterMessages, 2),
        Customer("Nackademin", 2000, nackademinMessages, 1)
    };
    const int customerCount = sizeof(customers) / sizeof(customers[0]);

    Customer* lastCustomer = nullptr;
    const char* lastMessage = nullptr;

    while (1) {
        // Select a customer based on weight
        Customer* selectedCustomer = selectCustomer(customers, customerCount, lastCustomer);
        lastCustomer = selectedCustomer;

        // Select a message ensuring no consecutive repeats
        const char* selectedMessage = selectedCustomer->getRandomMessage();
        while (selectedMessage == lastMessage) {
            selectedMessage = selectedCustomer->getRandomMessage();
        }
        lastMessage = selectedMessage;

        // Log customer, message, and weight to the UART
        printf("Customer: %s\n", selectedCustomer->getName());
        printf("Message: %s\n", selectedMessage);
        printf("Weight: %d\n", selectedCustomer->getDisplayWeight());

        // Display the message on the LCD
        lcd.Clear();
        lcd.WriteText((char*)selectedMessage);

        // Display for 20 seconds
        printf("Displaying message for 20 seconds...\n");
        custom_delay_ms(2000);

        printf("Message displayed successfully.\n");
    }

    return 0;
}
