#include "random.h"
#include <avr/io.h>  // For register access

unsigned int randomSeed = 13013; // Global random seed

// ADC initialization
void adcInit() {
    ADMUX = (1 << REFS0); // AVCC with external capacitor
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, prescaler = 64
}

// Timer1 initialization
void timer1Init() {
    TCCR1B = (1 << CS10); // Timer1 with no prescaling
}

// Read analog value from a specific pin
unsigned int readAnalog(uint8_t pin) {
    ADMUX = (ADMUX & 0xF8) | (pin & 0x07); // Select pin without affecting other bits
    ADCSRA |= (1 << ADSC); // Start conversion

    while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete

    return ADCW; // Return the ADC value
}

// Initialize random seed using ADC and Timer1
void initializeRandomSeed() {
    randomSeed = readAnalog(0) ^ (readAnalog(1) << 8) ^ (TCNT1 & 0xFFFF);
}

// Generate pseudo-random number
int pseudoRandom() {
    randomSeed = (randomSeed * 1664525 + 1013904223) & 0xFFFFFFFF; // 32-bit LCG
    return randomSeed & 0xFFFF; // Return lower 16 bits
}
