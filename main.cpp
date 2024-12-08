#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"
#include <string.h>

// https://wokwi.com/projects/416241646559459329

// PORTB B (digital pin 8 to 13)
// C (analog input pins)
// PORTD D (digital pins 0 to 7)
#define LED_PIN 2
#define BUTTON_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

class Customer {
public:
    char companyName[50];    
    char messages[3][50];    
    int amountPaid; 
    
    int messageCount;


    Customer(char name[], int paid = 0, int count = 0, char firstMessage[] = "", char secondMessage[] = "", char thirdMessage[] = ""){
        strcpy(companyName, name);
        strcpy(messages[0], firstMessage);
        if (count > 1){
            strcpy(messages[1], secondMessage);
        }
        if (count > 1){
            strcpy(messages[2], thirdMessage);
        }
        
            amountPaid = paid;
            messageCount = count;

    }
    };

    Customer customers[] = {
        Customer("Hederliga Harrys Bilar",
            5000,
            3,
            "köp bil hos harry",
            "En god bilaffär (för harry!)",
            "Hederliga harrys bilar"),
        
        Customer("Farmor Ankas pajer AB",
            3000,
            2,
            "Köp paj hos farmor anka",
            "Skynda innan mårten äter alla pajer"
            ),
           
         Customer("Svarte Petters Svartbyggen",
            1500,
            2,
            "Låt petter bygga åt dig",
            "Bygg Svart? Ring Petter"
            
             ),
            
        Customer("Långbens detektivbyrå",
            4000,
            2,
            "Mysterier? Ring Långben",
            "Långben fixar biffen"
            
             ),
            
        Customer("IOT24",
            1000,
            2,
            "IOT:s Reklambyrå"
            
            ),
    };
 




int main(void){
    
    //init_serial();
    HD44780 lcd;

    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD

    lcd.WriteText((char *)"Hej hej");
    //printf("Hej hej\n");
    //int r = 12;
    //printf("Hej 2 %d\n",r);
    // // //Sätt till INPUT_PULLUP
    // BIT_CLEAR(DDRB,BUTTON_PIN); // INPUT MODE
    // BIT_SET(PORTB,BUTTON_PIN); 

    // DATA DIRECTION = avgör mode
    // om output så skickar vi  1 eller 0 på motsvarande pinne på PORT
    // om input så läser vi  1 eller 0 på motsvarande pinne på PIN
    //bool blinking = false;
    while(1){
    }
    return 0;
}
