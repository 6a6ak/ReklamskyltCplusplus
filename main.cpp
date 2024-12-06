#include "lcd.h"
#include "customers.h"
#include "uart.h"
#include "utilities.h"  // Include for pseudoRandom
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

// Custom delay function for variable delays
void custom_delay_ms(int delayMs) {
    while (delayMs > 0) {
        if (delayMs >= 10) {
            _delay_ms(10); // Delay in chunks of 10ms
            delayMs -= 10;
        } else {
            _delay_ms(1); // Delay the remaining milliseconds
            delayMs--;
        }
    }
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

// Function to select a message for a customer ensuring no consecutive repeats
const char* selectMessage(Customer* customer, const char* lastMessage) {
    const char* selectedMessage = nullptr;
    while (selectedMessage == nullptr || selectedMessage == lastMessage) {
        selectedMessage = customer->getRandomMessage();
    }
    return selectedMessage;
}

int main(void) {
    // Seed the random number generator
    srand(12345); // Replace with a dynamic seed if desired

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

    const char nackademinMessages[][50] = {
        "   NackademiN"
    };
    Customer nackademin("Nackademin", 2000, nackademinMessages, 1); // Add Nackademin with payment and message

    // Create an array of customers
    Customer* customers[] = {&harry, &anka, &petter, &nackademin}; // Add Nackademin to the array
    int customerCount = sizeof(customers) / sizeof(customers[0]);

    // Track last displayed customer and messages
    Customer* lastCustomer = nullptr;
    const char* lastMessage = nullptr;

    // Dynamic message display
    while (1) {
        // Select a customer based on payment weight
        Customer* selectedCustomer = selectCustomer(customers, customerCount, lastCustomer);
        lastCustomer = selectedCustomer;

        // Select a message for the customer ensuring no consecutive repeats
        const char* selectedMessage = selectMessage(selectedCustomer, lastMessage);
        lastMessage = selectedMessage;

        // Calculate the weight value of the selected customer
        int customerWeight = selectedCustomer->getDisplayWeight();

        // Log selected customer, message, and weight on the terminal
        printf("Selected Customer: %s\n", selectedCustomer->getName());
        printf("Message: %s\n", selectedMessage);
        printf("Weight Value: %d\n", customerWeight);

        // Display the selected message on the LCD
        lcd.Clear();
        lcd.WriteText((char*)selectedMessage);

        // Fixed display time for all messages (20 seconds)
        printf("Displaying message for 20 seconds...\n");
        custom_delay_ms(2000);

        printf("Message displayed successfully.\n");
    }

    return 0;
}
