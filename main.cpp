#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Include for atoi
#include "lcd.h"
#include "uart.h"
#include "Costumer.h"

// https://wokwi.com/projects/416241646559459329

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

void sendCostumerData(const Costumer& costumer) {
    uart_puts("Company Name: ");
    uart_puts(costumer.getCompanyName());
    uart_puts("\nMessage 1: ");
    uart_puts(costumer.getMessage1());
    uart_puts("\nMessage 2: ");
    uart_puts(costumer.getMessage2());
    uart_puts("\nMessage 3: ");
    uart_puts(costumer.getMessage3());
    uart_puts("\nPay: ");
    char payStr[10];
    sprintf(payStr, "%d", costumer.getPay());
    uart_puts(payStr);
    uart_puts("\n");
}

void receiveCostumerData(Costumer& costumer) {
    char buffer[100];
    uart_gets(buffer, sizeof(buffer));
    costumer.setCompanyName(buffer);

    uart_gets(buffer, sizeof(buffer));
    costumer.setMessage1(buffer);

    uart_gets(buffer, sizeof(buffer));
    costumer.setMessage2(buffer);

    uart_gets(buffer, sizeof(buffer));
    costumer.setMessage3(buffer);

    uart_gets(buffer, sizeof(buffer));
    costumer.setPay(atoi(buffer));
}

int main(void)
{
    HD44780 lcd;
    uart_init();

    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD

    Costumer Harry("CompanyName", "Message1", "Message2", "Message3", 5000);

    // Send initial data to serial port
    sendCostumerData(Harry);

    // Receive new data from serial port
    receiveCostumerData(Harry);

    // Display updated data on LCD
    lcd.WriteText(Harry.getMessage1());

    while (1)
    {
    }
    return 0;
}