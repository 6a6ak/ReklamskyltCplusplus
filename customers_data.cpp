#include "customers_data.h"

// Define customer messages
const char harryMessages[][50] = {
    "Buy a car from       Harry!",
    "  A good deal    (for Harry !)",
    "Honest Harry's        Cars"};
const char ankaMessages[][50] = {
    " Buy pies from        Anka!",
    " Hurry, before   they are gone!"};
const char petterMessages[][50] = {
    "Let Petter build    for you!",
    "Building black?   Call Petter!"};
const char langbenMessages[][50] = {
    "Mysterier?      Ring Langben",
    "Langben fixar      biffen"};
const char nackademinMessages[][50] = {
    "-=[NackademiN]=-     IoT 24"};

// Define customers array
Customer customers[] = {
    Customer("Harry", 5000, harryMessages, 3),
    Customer("Anka", 3000, ankaMessages, 2),
    Customer("Petter", 1500, petterMessages, 2),
    Customer("Langbens detektivbyra", 4000, langbenMessages, 2),
    Customer("Nackademin", 2000, nackademinMessages, 1)};

// Define the total number of customers
const int customerCount = sizeof(customers) / sizeof(customers[0]);
