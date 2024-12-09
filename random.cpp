#include "random.h"
#include <avr/io.h>  // For register access

unsigned int randomSeed = 7; // Global random seed

// Function to initialize the ADC and read analog value from a specific pin
unsigned int readAnalog(uint8_t pin) {
    // Configure ADC
    ADMUX = (1 << REFS0) | (pin & 0x07); // AVCC with external capacitor, select pin
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, start conversion, prescaler = 64

    while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete

    return ADCW; // Return the ADC value
}

// Function to initialize random seed using analog pin
void initializeRandomSeed() {
    randomSeed = readAnalog(0); // Directly set randomSeed with the value from A0
}

// Pseudo-random number generator function
int pseudoRandom() {
    randomSeed = (randomSeed * 1103515245 + 12345) & 0x7FFF; // Generate next pseudo-random number
    return randomSeed;
}
