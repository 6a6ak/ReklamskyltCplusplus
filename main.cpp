<<<<<<< HEAD
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
    initializeRandomSeed();
    // randomSeed = 12345;

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


int randomValue = pseudoRandom();
    printf("Random value: %d\n", randomValue);

=======
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"
#include "Costumer.h"

#define LED_PIN 2
#define BUTTON_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b))))

#define BUTTON_IS_CLICKED(PINB, BUTTON_PIN) !BIT_CHECK(PINB, BUTTON_PIN)

// https://wokwi.com/projects/416241646559459329



// Function to display customer information on the LCD
void DisplayCostumerInfo(HD44780 *lcd, Costumer *customer)
{
    char buffer[20];
    lcd->Clear();
    lcd->WriteText(customer->GetCompanyName()); // Display the company name
    _delay_ms(2000);

    for (int i = 0; i < 3; i++)
    { // Display each message
        lcd->Clear();
        lcd->WriteText(customer->GetMessage(i));
        _delay_ms(2000);
    }

    lcd->Clear();
    sprintf(buffer, "Pay: %d", customer->GetPay()); // Prepare payment information
    lcd->WriteText(buffer);                         // Display payment
    _delay_ms(2000);
}

int main(void)
{
    // Initialize UART for debugging
    init_serial();
    printf("UART initialized\n");

    HD44780 lcd;
    lcd.Initialize(); // Initialize the LCD
    printf("LCD initialized\n");
    lcd.Clear();
    printf("LCD cleared\n");

    // Create a customer instance
    Costumer Harry("Hederlige Harrys Bilar", "Köp bil hos Harry", "En god bilaffär (för Harry!)", "Hederlige Harrys Bilar", 4000);

    // Directly display customer information without button press
    DisplayCostumerInfo(&lcd, &Harry);

    // Infinite loop to keep the program running
    while (1)
    {
        // You can add code here for other functionalities, such as button handling or LED control
    }

>>>>>>> fa46c9aece16cb6cbdcb2b7736ebb8142e74d190
    return 0;
}
