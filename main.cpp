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

    return 0;
}
