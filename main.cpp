#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"
#include "Costumer.h"
#include <stdlib.h>



#define LED_PIN 2
#define BUTTON_PIN 1
#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 
#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

// https://wokwi.com/projects/416241646559459329




int main(void){
    init_serial(); 
    HD44780 lcd;

    lcd.Initialize();
    lcd.Clear();

    // Hederlige Harrys Bilar 5000
    Costumer Harry("Kop bil hos Harry", "En god bilaffar (for Harry!)", "Hederlige Harrys Bilar");

    //Långbens detektivbyrå 4000
    Costumer LångBen("Mysterier? Ring Langben", "Langben fixar biffen", "Message3");
  
    // Farmor Ankas Pajer AB 3000
    Costumer Anka("Kop paj hos Farmor Anka", "Skynda innan Marten atit alla pajer", "Message3");

    //Svarte Petters Svartbyggen 1500
    Costumer Petter("Lat Petter bygga at dig", "Bygga svart? Ring Petter", "Message3");


    // GetCompanyName(), GetMessage(0,1,2)
    // lcd.WriteText(Harry.GetCompanyName());


while (1) {
    int Random = rand() % 136;
    int RND = rand() % 4;
    printf("Random: %d, RND: %d\n", Random, RND);

    if (Random <= 50) {
        switch (RND) {
            case 0:
            case 1:
                lcd.WriteText(Harry.GetMessage(0));
                break;
            case 2:
                lcd.WriteText(Harry.GetMessage(1));
                break;
            case 3:
                lcd.WriteText(Harry.GetMessage(2));
                break;
        }
    } else if (Random > 50 && Random <= 90) {
        lcd.WriteText(LångBen.GetMessage(0));
    } else if (Random > 90 && Random <= 110) {
        switch (RND) {
            case 0:
            case 1:
                lcd.WriteText(Anka.GetMessage(0));
                break;
            case 2:
            case 3:
                lcd.WriteText(Anka.GetMessage(1));
                break;
        }
    } else {
        lcd.WriteText(Petter.GetMessage(0));
    }

    _delay_ms(5000);
    lcd.Clear();
}


    return 0;
}
