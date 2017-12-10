/* Nolen Johnson
* COP3223C-17Fall 0R04 - Project 6: TreasureChest
* Allows a user to guess which keys unlock a treasure chest, reads the real set of keys from a file, and lets the user know how many they got correct/if they were able to open the chest.
*/

// Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define Constants
#define NUM_KEYS 7

int main(void)
{

// Store this as a char, and set it to 1 until we set it to 0 to exit.
char guessing=1;
// Declare our integers
int h, i, j, k, n, correct_keys = 0, correctly_ordered_keys = 0, duplicates = 0;
// Declare our integer arrays
int guessed_keys[NUM_KEYS], real_keys[NUM_KEYS];

// Declare file pointer
FILE * ifp;

// Store this as a char
char filename[30];

// Query the user for the name of the file.
printf("What is the name of the file?\n");
scanf("%s", filename);

// Initialize the file pointer
ifp = fopen(filename, "r");
    // Is the file valid?/Does it exist?/Do we have permissions to view it?
    if(!ifp)
    {
        printf("\n Unable to open the file");
        return 0;
    }

// Scan the real keys into an array
for (k = 0; k < NUM_KEYS; k++){
fscanf(ifp, "%d", &real_keys[k]);
}

// Loop 1 - Dictates whether the user is in a state of guessing or not.
while(guessing == 1) {

// Yet another Cutesy Pirate Intro
printf("------------------------------- \n");
printf("To get to me treasure you'll have to figure out which of me 100 keys are used in the 7 locks of me treasure chest. \n\n");

// Query the user for their 7 guesses, and store them in an array
printf("Which keys will ye use? \n");
for(i = 0; i < NUM_KEYS; ++i){
    if (scanf("%d", &n) == -1)
        break;
    guessed_keys[i] = n;
}
puts ("");

// I've indented all the mathematical functions for organization's sake.

    // Keep track of how many keys are correct
    for(h=0; h < NUM_KEYS; h++) {
        // We use a nested loop so we can check each digit of one array against all of the other
        for(j=0; j < NUM_KEYS; j++){
            // Now we compare the values in the array
            if(real_keys[h] == guessed_keys[j]) {
                correct_keys++;
            }
        }
    }

    // Keep track of how many keys are in the correct order
    for(h=0; h < NUM_KEYS; h++) {
        if(real_keys[h] == guessed_keys[h]) {
            correctly_ordered_keys++;
            }
        }

    // Check for Duplicate inputs
    for (i = 0; i < NUM_KEYS - 1; i++) {
        for (j = i + 1; j < NUM_KEYS; j++) {
            if (guessed_keys[i] == guessed_keys[j]) {
                duplicates = 1;
            }
        }
    }

// Check if the user input the correct keys in the correct order (no need to define duplicates, as having duplicates and the correctly ordered keys are impossible in the given scenario) [1/3]
if (correctly_ordered_keys == NUM_KEYS){
    // Tell the user they've opened the chest
    printf("Arr! You've opened me treasure chest and found...\n");
    printf("A map! To the rest of me treasure on Treasure Island.\n");
    printf("Hahaha!\n");
    guessing = 0;
    }

// If not, check if they have some keys correct regardless of order, as long as there aren't duplicates.[2/3]
else if (correct_keys <= NUM_KEYS && correctly_ordered_keys != NUM_KEYS && duplicates != 1){
    // Tell the user how many keys they have right regardless of their order
    printf("%d of those keys are correct, matey!  But are they in the right order?\n", correct_keys);
    }

// If not, check if there are duplicates.
else if (duplicates == 1) {
    //Tell the user duplicate inputs are not permitted.
    printf("You can only use each key once, matey!\n");
    }

// It is logically impossible to have an outcome that doesn't fall in one of these 3 if statements given the assignment parameters

}
return 0;
}

