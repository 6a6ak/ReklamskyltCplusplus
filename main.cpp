#include "lcd.h"
#include "customers_data.h"
#include "utilities.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Delay function for millisecond delays
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

// Function to shuffle customer order for randomness
void shuffleCustomers(Customer* customers[], int count) {
    for (int i = count - 1; i > 0; --i) {
        int j = pseudoRandom() % (i + 1);
        Customer* temp = customers[i];
        customers[i] = customers[j];
        customers[j] = temp;
    }
}

int main() {
    // Seed the random number generator
    randomSeed = 12345;

    // Initialize the LCD
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();

    // Initialize UART for debugging
    init_serial();
    printf("UART Initialized. Starting program...\n");

    // Array to hold pointers to customers
    Customer* customerPointers[customerCount];
    for (int i = 0; i < customerCount; ++i) {
        customerPointers[i] = &customers[i];
    }

    // Start the main loop
    while (1) {
        // Shuffle customers for randomness in each round
        shuffleCustomers(customerPointers, customerCount);

        // Display ads for each customer in the shuffled order
        for (int i = 0; i < customerCount; ++i) {
            Customer* selectedCustomer = customerPointers[i];

            // Display all messages for the current customer
            for (int j = 0; j < selectedCustomer->getMessageCount(); ++j) {
                const char* message = selectedCustomer->getMessage(j);

                // Display the message on the LCD
                lcd.Clear();
                lcd.WriteText((char*)message);

                // Log to the serial port
                printf("Customer: %s\nMessage: %s\n", selectedCustomer->getName(), message);

                // Display message for 20 seconds
                custom_delay_ms(2000);
            }
        }

        // Log end of round
        printf("Completed one round of displaying all ads.\n");
    }

    return 0;
}
