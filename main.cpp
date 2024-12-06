#include "lcd.h"
#include "customers.h"
#include "uart.h"  // Add UART header
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h> // For printf

// Simple pseudo-random number generator
unsigned int randomSeed = 12345;

int pseudoRandom() {
    randomSeed = (randomSeed * 1103515245 + 12345) & 0x7FFF;
    return randomSeed;
}

// Function to select the next customer based on weights
Customer* selectCustomer(Customer* customers[], int customerCount, Customer* lastCustomer) {
    int totalWeight = 0;

    // Calculate total weight
    for (int i = 0; i < customerCount; ++i) {
        totalWeight += customers[i]->getDisplayWeight();
    }

    Customer* selectedCustomer = nullptr;
    while (selectedCustomer == nullptr || selectedCustomer == lastCustomer) {
        int randomWeight = pseudoRandom() % totalWeight;
        for (int i = 0; i < customerCount; ++i) {
            randomWeight -= customers[i]->getDisplayWeight();
            if (randomWeight < 0) {
                selectedCustomer = customers[i];
                break;
            }
        }
    }
    return selectedCustomer;
}

int main(void) {
    // Initialize the LCD
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();

    // Initialize UART for debugging
    init_serial(); 
    printf("UART Initialized. Starting program...\n");

    // Define customers and their messages
    const char harryMessages[][50] = {
        "Buy a car from Harry!",
        "A good deal (for Harry!)",
        "Honest Harry's Cars"
    };
    Customer harry("Harry", 5000, harryMessages, 3);

    const char ankaMessages[][50] = {
        "Buy pies from Anka!",
        "Hurry, before they are gone!"
    };
    Customer anka("Anka", 3000, ankaMessages, 2);

    const char petterMessages[][50] = {
        "Let Petter build for you!",
        "Building black? Call Petter!"
    };
    Customer petter("Petter", 1500, petterMessages, 2);

    // Create an array of customers
    Customer* customers[] = {&harry, &anka, &petter};
    int customerCount = sizeof(customers) / sizeof(customers[0]);

    // Last displayed customer
    Customer* lastCustomer = nullptr;

    // Display messages dynamically
    while (1) {
        // Select a customer based on payment weight
        Customer* selectedCustomer = selectCustomer(customers, customerCount, lastCustomer);
        lastCustomer = selectedCustomer;

        // Log selected customer and message
        printf("Selected Customer: %s\n", selectedCustomer->getName());
        printf("Message: %s\n", selectedCustomer->getRandomMessage());

        // Display a random message from the selected customer
        lcd.Clear();
        lcd.WriteText((char*)selectedCustomer->getRandomMessage());

        // Calculate delay time based on payment (e.g., 1 second per 1000 payment)
        int delayTime = selectedCustomer->getPayment() / 1000; // Delay in seconds
        printf("Delay Time: %d seconds\n", delayTime);

        // Apply delay and log each second
        for (int i = 0; i < delayTime; ++i) {
            _delay_ms(1000);
            printf("Delay second: %d\n", i + 1);
        }
    }

    return 0;
}
