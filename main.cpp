#include "lcd.h"
#include "customers.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // For rand() and srand()
#include <stdio.h>

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

// Display all messages for each customer at least once
void displayAllMessages(HD44780& lcd, Customer* customers[], int customerCount) {
    for (int i = 0; i < customerCount; ++i) {
        Customer* currentCustomer = customers[i];
        int messageCount = currentCustomer->getMessageCount();
        for (int j = 0; j < messageCount; ++j) {
            const char* message = currentCustomer->getMessage(j);
            lcd.Clear();
            lcd.WriteText((char*)message);
            printf("Customer: %s, Message: %s, Display Time: 20 seconds\n", currentCustomer->getName(), message);
            custom_delay_ms(2000); // Display each message for 2 seconds
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
        int randomWeight = rand() % totalWeight; // Use rand() from stdlib.h
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
    // Seed the random number generator
    srand(12345); // You can replace 12345 with dynamic seeds like time-based values

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

    // **Step 1: Ensure all messages are displayed once**
    printf("Starting first round: Displaying all messages for each customer...\n");
    displayAllMessages(lcd, customers, customerCount);

    // **Step 2: Display messages dynamically based on payment weight**
    printf("Starting second round: Dynamic message display...\n");
    Customer* lastCustomer = nullptr;

    while (1) {
        // Select a customer based on payment weight
        Customer* selectedCustomer = selectCustomer(customers, customerCount, lastCustomer);
        lastCustomer = selectedCustomer;

        // Log selected customer and message
        const char* selectedMessage = selectedCustomer->getRandomMessage();
        printf("Selected Customer: %s\n", selectedCustomer->getName());
        printf("Message: %s\n", selectedMessage);

        // Display the selected message on the LCD
        lcd.Clear();
        lcd.WriteText((char*)selectedMessage);

        // Calculate total delay in milliseconds
        int totalDelayMs = selectedCustomer->getPayment(); // Delay based on payment amount
        printf("Delay Time: %d ms\n", totalDelayMs);

        // Apply the custom delay
        custom_delay_ms(totalDelayMs);

        printf("Delay completed for customer: %s\n", selectedCustomer->getName());
    }

    return 0;
}
