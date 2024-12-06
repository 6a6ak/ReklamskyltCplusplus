#include "utilities.h"

// Define the global random seed variable
unsigned int randomSeed = 12345;

// Pseudo-random number generator function
int pseudoRandom() {
    randomSeed = (randomSeed * 1103515245 + 12345) & 0x7FFF;
    return randomSeed;
}
