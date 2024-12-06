#include "utilities.h"

unsigned int randomSeed = 12345; // Global random seed

// Pseudo-random number generator function
int pseudoRandom() {
    randomSeed = (randomSeed * 1103515245 + 12345) & 0x7FFF;
    return randomSeed;
}
