#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"

// PORTB B (digital pin 8 to 13)
// C (analog input pins)
// PORTD D (digital pins 0 to 7)
#define LED_PIN 2
#define BUTTON_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b))))

#define BUTTON_IS_CLICKED(PINB, BUTTON_PIN) !BIT_CHECK(PINB, BUTTON_PIN)

int main(void)
{
    // Initialize UART and LCD
    init_serial(); // Initialize UART for serial communication
    HD44780 lcd;   // Create an instance of the LCD class

    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD display

    // Write text to the first line
    lcd.WriteText((char *)"Hej Babak");

    // Move cursor to the second line (row 1, column 0)
    lcd.GoTo(0, 1); // Ensure correct row and column parameters
    lcd.WriteText((char *)"Hej in line 2");

    // Output messages to the terminal via UART
    printf("Hej Babak in terminal\n");
    int r = 12;
    printf("Hej 2 %d\n", r);

    // Infinite loop
    while (1)
    {
        // You can add code here for other functionalities, such as button handling or LED control
    }

    return 0;
}
