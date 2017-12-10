/* Nolen Johnson
* COP3223C-17Fall 0R04 - Project 1: PirateCrew - 09/20/17
* Serves as a potential pirate crew members interview, and tells them whether or not they can join the crew.
*/

//Included Libraries
#include <stdio.h>

//No Constants to Define

//main function
int main(){

//Store user response to yes/no question as y/n, and therefor, use char datatype
/* NOTE: When using char data-types, the format specifier %c seems to have some unexplainable oddities when polled from the user through the standard C scanf function (i.e. scanf won't actually query the user).
* This resulted in me deciding to use the format specifier %s (for string).
*/
char likes_digging_for_treasure, can_swim;
// Unlike the above variables, the distance's that will be put in are going to be greater than or equal to 0, meaning that an integer will work in this case.
int swim_distance;

    // Query the user about whether or not they enjoy digging for treasure
    printf("Do you like digging for treasure? (y/n).\n");
    scanf("%s", &likes_digging_for_treasure);

    // Question requires y/n input, if the input is not one of those, it is invalid.
    //If Statement 1
    if (likes_digging_for_treasure == 'n' || likes_digging_for_treasure == 'N') {
        printf("You can't join the crew.\n\n");

    } else if (likes_digging_for_treasure == 'y' || likes_digging_for_treasure == 'Y') {
        printf("Good.\n\n");
        // Query the user about their ability to swim.
        printf("Can you swim? (y/n).\n");
        scanf("%s", &can_swim);

        //If Statement 2
        if (can_swim == 'y' || can_swim == 'Y') {
            printf("Good.\n\n");
            // Query the user about how far they can swim.
            printf("How many meters are you able to swim?\n");
            scanf("%i", &swim_distance);

            //If Statement 3
            //Due to the assignment's specification that the input would be specific, type validation is not necessary for this input.
            //If the user can't swim 100 or more meters, they are not eligible to join the crew
            if (swim_distance >= 100) {
                printf("You may join the pirate crew!  Arrr!\n\n");
            } else {
                printf("You can't join the crew.\n");
            }
            //End If Statement 3

        } else if (can_swim == 'n' || can_swim == 'N') {
        printf("You can't join the crew.\n\n");
        } else {
        printf("Your input was invalid.\n\n");
        }
        //End If Statement 2

    } else {
        printf("Your input was invalid.\n\n");
    }
    //End If Statement 1
    return 0;
}
