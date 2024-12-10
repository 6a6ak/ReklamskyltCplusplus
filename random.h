#ifndef RANDOM_H
#define RANDOM_H

extern unsigned int randomSeed; // Global random seed

// Initialize the random seed
void initializeRandomSeed();

// Pseudo-random number generator function
int pseudoRandom();

#endif
