/* Nolen Johnson
* COP3223C-17Fall 0R04 - Project 1: PiratePrep - 08/31/17
* Calculates the number of oranges a pirate captain will need to keep his crew scurvy free over any number of kilometers & with any amount of crew members
*/

//Included Libraries
#include <stdio.h>

//Define Constants
#define KILOMETERS_FROM_SPAIN_TO_CARIBBEAN 7228
#define ORANGES_PER_CREW_MEMBER 1/2

//main function
int main() {

// We use double instead of float here because a float can store 4 bytes, whereas a double can store 8 bytes, making larger outputs possible
double ship_kilometers_per_day, ship_crew_members, necessary_num_oranges;

    // Cutesy Pirate Intro
    printf("ARGH Mateys, so you be wantin' to set course for the Caribbean ay?\n\n");
    printf("In that case, we ought to figure a way to keep you and your crew scurvy free.\n\n");
    printf("Oranges will solve yer problem, but to tell you how many you'll need, I'll be needin to know some things;\n\n");

    // Query the user about their ship's traveling capabilities
    printf("How many kilometers can your ship travel a day?\n");
    scanf("%lf", &ship_kilometers_per_day  );

    // Query the user about their ship's carrying capacity
    printf("How many crew members can your ship hold?\n");
    scanf("%lf", &ship_crew_members );

    // Calculate number of oranges necessary
    // Parentheses would normally be necessary, but due to multiplication/division being in the same precedence level, it does not matter in this problem
    // TODO: We can't handle absurdly large numbers (i.e. if output is less than 2.3E-308 or greater than 1.7E+308) due to data type size constraints
    necessary_num_oranges = KILOMETERS_FROM_SPAIN_TO_CARIBBEAN/ship_kilometers_per_day*ship_crew_members*ORANGES_PER_CREW_MEMBER;

    // Prevent outputting non-real numbers/error outputs (solves -1.#J output when either variable is equal to 0), there's probably an external header that can help solve this issue
    if (ship_crew_members == 0, ship_kilometers_per_day == 0) {
        printf("You won't need any oranges.\n\n");
    }
    else {
        // Print necessary number of oranges to user (out to two decimal places)
        printf("You will need %.02lf oranges to make the trip!\n\n",necessary_num_oranges );
        }

return 0;
}
