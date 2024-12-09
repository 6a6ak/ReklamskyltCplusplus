#include "lcd.h"
#include "customers_data.h"
#include "random.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
// Custom delay function
void custom_delay_ms(int delayMs)
{
    while (delayMs > 0)
    {
        if (delayMs >= 10)
        {
            _delay_ms(10);
            delayMs -= 10;
        }
        else
        {
            _delay_ms(1);
            delayMs--;
        }
    }
}
// Main function
int main()
{
    initializeRandomSeed();
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();
    init_serial();
    printf("UART Initialized. Starting...\n");

    const char *lastMessage = nullptr; 
    Customer *lastCustomer = nullptr;

    while (1)
    {
        Customer *selectedCustomer = nullptr;
        int customerAttempts = 0;
        const int maxAttempts = 10;

        
        while (customerAttempts < customerCount)
        {
            int randomIndex = pseudoRandom() % customerCount;
            selectedCustomer = &customers[randomIndex];

            
            if (selectedCustomer != lastCustomer &&
                selectedCustomer->getMessageCount() > 0 &&
                selectedCustomer->getDisplayWeight() > 0)
                break;

            customerAttempts++;
        }
// If no valid customer is found, restart the loop
        if (!selectedCustomer || customerAttempts >= customerCount)
        {
            printf("Error: Unable to find a valid customer. Restarting...\n");
            continue;
        }

        const char *message = nullptr;
        int messageAttempts = 0;
//
        
        while (messageAttempts < selectedCustomer->getMessageCount())
        {
            message = selectedCustomer->getRandomMessage();

            
            if (message != nullptr && message[0] != '\0' && strcmp(message, lastMessage) != 0)
                break;

            messageAttempts++;
        }
// If no valid message is found, restart the loop
        if (!message || messageAttempts >= selectedCustomer->getMessageCount())
        {
            
            printf("Warning: Message from customer %s is repeated or invalid. Keeping previous message.\n", selectedCustomer->getName());
            continue; 
        }

        
        lcd.Clear();
        lcd.WriteText((char *)message);

        printf("Customer: %s (Weight: %d)\nMessage: %s\n",
               selectedCustomer->getName(),
               selectedCustomer->getDisplayWeight(),
               message);

        
        lastMessage = message;
        lastCustomer = selectedCustomer;

        custom_delay_ms(2000);
    }

    return 0;
}
