#include "lcd.h"
#include "customers.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Initialize the LCD
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();

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

    // Display random messages in a loop
    while (1) {
        lcd.Clear();
        lcd.WriteText((char*)harry.getRandomMessage());
        _delay_ms(3000); // Wait for 3 seconds

        lcd.Clear();
        lcd.WriteText((char*)anka.getRandomMessage());
        _delay_ms(3000); // Wait for 3 seconds
    }

    return 0;
}
