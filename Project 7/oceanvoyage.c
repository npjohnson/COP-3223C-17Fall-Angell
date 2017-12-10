/* Nolen Johnson
* OceanVoyage
* Keeps track of your journey, supplies, and crew members status when traveling to the destination on the old pirates map.
*/

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Constants for Arrays
#define STRLENGTH 30
#define NUMCREW 5
#define NUMSUPPLIES 4

//Constants for Distances (measured in miles)
#define CANARY 1261
#define GRENADA 3110
#define FINAL 500
#define DISTANCE 4871

//Function Signatures - do not change these
void setup(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int *captaintype, int *funds, int *distanceperday);
int countcrew(int crewstatus[NUMCREW]);
void printstatus(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW]);
void getsupplies(char supplytypes[NUMSUPPLIES][STRLENGTH], int supplies[NUMSUPPLIES], int *funds);
void dailyreport(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int funds, int traveled);
void rest(int supplies[NUMSUPPLIES], char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days);
int fish();
int max(int a, int b);
int min(int a, int b);
void event(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days, int supplies[NUMSUPPLIES]);

//Main function - This is the final version of main.  Any changes you make while
//creating the functions should be removed prior to submission.
int main(void) {
    //crewnames and supplytypes are arrays of strings to store the names of the crew members
    //and the types of supplies that can be purchased and taken on the voyage
    char crewnames[NUMCREW][STRLENGTH];
    char supplytypes[NUMSUPPLIES][STRLENGTH] = {"Food", "Clothes", "Ship Parts", "Shovels"};
    //stop indicates whether or not the user would like to stop at a port
    //crewstatus indicates the status of each crew member, corresponding to the order of names
    //supplies has a total for each type of supply, corresponding to the order of supplies
    char stop;
    int crewstatus[NUMCREW], supplies[NUMSUPPLIES];
    //the distanceperday and funds depends on the captaintype the user selects
    //day is the current day, traveled is the total miles traveled, i is a loop counter
    //and action stores the intended action of the user for the day
    int distanceperday, captaintype, funds, traveled=0, day=1;
    int i, action;

    //seed the pseudorandom number generator
    srand(time(0));

    //initialize each variable with information from the user
    setup(crewnames, crewstatus, supplies, &captaintype, &funds, &distanceperday);

    //begin the game by purchasing initial supplies
    printf("\nBefore leaving Port Marin, you should purchase some supplies.\n");
    getsupplies(supplytypes, supplies, &funds);

    //continue the voyage until the ship reaches the intended destination
    //if all crew members perish, the journey cannot continui
    while (traveled < DISTANCE && countcrew(crewstatus) > 0) {
        printf("\n\n--It is day #%d.--\n", day);

        //check to see if the ship has reached the next port
        if(traveled >= (GRENADA+CANARY) && traveled < (GRENADA + CANARY + distanceperday) ) {
            printf("You have arrived at Grenada, at the edge of the Carribbean Sea.\n");
            printf("Would you like to make port? (Y/N)\n");
            scanf(" %c", &stop);

            if (stop == 'Y' || stop == 'y')
                getsupplies(supplytypes, supplies, &funds);

            traveled = (GRENADA+CANARY) + distanceperday;
        }
        else if (traveled >= CANARY && traveled < (CANARY + distanceperday) ) {
            printf("You have arrived at the Canary Islands.\n");
            printf("Would you like to make port? (Y/N)\n");
            scanf(" %c", &stop);

            if (stop == 'Y' || stop == 'y')
                getsupplies(supplytypes, supplies, &funds);

            traveled = CANARY + distanceperday;
        }
        //if between destinations: print the daily report and process the user's action for the day
        else {
            dailyreport(crewnames, crewstatus, supplies, funds, traveled);

            printf("\nWhat would you like to do?\n");
            printf("1 - Fish\n");
            printf("2 - Rest\n");
            printf("3 - Continue\n");
            scanf("%d", &action);

            if(action == 1) {
                supplies[0] += fish();
            }
            else if(action == 2) {
                day--;
                rest(supplies, crewnames, crewstatus, &day);
            }
            else {
                traveled += distanceperday;
                supplies[0] = max(supplies[0] - countcrew(crewstatus) * 2, 0);
                event(crewnames, crewstatus, &day, supplies);
            }
        }
        day++;
    }

    printf("\n\n");

    //The final printout changes based on which condition broke the while loop
    if (countcrew(crewstatus) == 0) {
        printf("Your crew has perished in the search for treasure. :(\n");

        printstatus(crewnames, crewstatus);
    }
    else {
        printf("Your crew has made it safely to the island.\n");

        printstatus(crewnames, crewstatus);

        if(supplies[3] >= countcrew(crewstatus))
            printf("You have enough shovels to dig up the treasure!\n");
        else
            printf("Unfortuantely, you will not be able to dig up the treasure.\n");
    }

    return 0;
}

//Pre-conditions:  none
//Post-conditions: each input parameter should be assigned an initial value

//What to do in this function: Provide the starting message for the user and ask how they plan to travel.
//  Based on their response initialize captaintype, funds, and distanceperday
//  -captaintype 1 should get 1000 funds and 80 distanceperday
//  -captaintype 2 should get 900 funds and 90 distanceperday
//  -captaintype 3 should get 800 funds and 100 distanceperday

//  Ask the user for their name.  Place this in the first row of crewnames, representing the captain.  Treat
//  crewnames as a 1-Dimensional array of strings. As an example: printf("%s", crewnames[0]); would print the
//  first string or the captains name to the screen.  Then ask for the names of the other 4 crew members in a loop.

//  Set the crew status to 2 for each crew member, representing healthy
//  Set the initial amount of supplies to be 0 for each supply
/** TODO: Fix invalid input to be able to deal with letters (it freaks out right now) **/
void setup(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int *captaintype, int *funds, int *distanceperday) {

// Query the user about what type of captain they are
printf("You may now take your ship and crew from Port Marin, Spain to the hidden island in the Caribbean on the old pirate's map.\n\n");

printf("How will you travel?\n");
printf("1 - As a merchant\n");
printf("2 - As a privateer\n");
printf("3 - As a pirate\n");
scanf("%d", &captaintype);

// This lets us cleanly store the captaintype label without needing an array (using string.h).
size_t name;

// Assign captaintype, and teh corresponding funds, distanceperday, and name based on user input, check for invalid input.
    if (captaintype == 1) {
        *funds = 1000;
        *distanceperday = 80;
        name = "merchant";
    }
    if (captaintype == 2) {
        *funds = 900;
        *distanceperday = 90;
        name = "privateer";
    }
    if (captaintype == 3) {
        *funds = 800;
        *distanceperday = 100;
        name = "pirate";
    }
    if (captaintype != 1 && captaintype != 2 && captaintype != 3) {
        printf("Invalid Input Detected\n");
}

// Tell the user what their captaintype gets.
printf("As a %s, you begin your trip with %d gold pieces.\n", name, *funds);
printf("You will be sailing your Clipper, with an average speed of %d miles per day.\n\n", *distanceperday);

// Query the user for their name.
printf("What is your name, Captain?\n");
scanf("%s",&crewnames[0]);

printf("%s\n", crewnames[0]);

// Query the user for additional crew member's names
printf("Who are the other members of your crew?\n");

int i;

// Traverse the crewname array and scan strings into each row. Subtract 1 from NUMCREW to account for the captains name already being in the array, add 1 to i in crewnames[] to again account for the captains name being at position 0
for(i=0;i<NUMCREW-1;i++) {
    scanf("%s",&crewnames[i+1]);
    }

// Print crew names starting with the 1st (array position 0)
for(i=0;i<NUMCREW;i++) {
    printf("%d:%s\n", i+1, crewnames[i]);
    }

// All crew members start healthy
for(i=0;i<NUMCREW;i++) {
    crewstatus[i] = 2;
    }

// All supply values start at 0
for(i=0;i<NUMSUPPLIES;i++) {
    supplies[i] = 0;
    }

return;

}

//Pre-conditions:  crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//Post-conditions: returns the number of crew members that are alive

//What to do in this function: Traverse the crew status array and count how many crew members
//  have a status that is not 0.  Return this count.
int countcrew(int crewstatus[NUMCREW]) {

int i, numalive=0;
// Traverse the array and for everyone not dead, increment numalive.
for(i=0;i<NUMCREW;i++) {
    if (crewstatus[i] != 0) {
        numalive = numalive+1;
    }
}
return numalive;
}

//Pre-conditions:  crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//Post-conditions: none

//What to do in this function: print each crew members name and their status.
//  You may use a status array to shorten this process: char status[3][STRLENGTH] = {"Deceased", "Ill", "Healthy"};
void printstatus(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW]) {

char status[3][STRLENGTH] = {"Deceased", "Ill", "Healthy"};

// Traverse the array and print crew names & their status
int i;
for(i=0;i<NUMCREW;i++) {
    printf("%s: %s\n",crewnames[i],status[crewstatus[i]]);
    }
printf("\n");
return;
}

//Pre-conditions:  supplytypes in an array of strings and gives the name of each supply type
//                 supplies is an array of integers representing how many of each type the crew has
//                 funds represents how many gold pieces the crew has to spend
//Post-conditions: the user may choose to buy supplies: incrementing values in supplies and
//                 decrementing funds

//What to do in this function: First print out the amount of gold the crew has.
//  Then print each supply type and the amount it costs.  You may use a cost array to shorten
//  this process: int supplycosts[NUMSUPPLIES] = {1, 2, 20, 10};
//  Based on the user's selection, ask the user how many of that supply they would like to buy.
//  Verify that the user has enough gold for their purchase and update the correct index of supplies.
//  Deduct the corresponding amount from the user's funds.
void getsupplies(char supplytypes[NUMSUPPLIES][STRLENGTH], int supplies[NUMSUPPLIES], int *funds) {

int r, shopping=1, numbought=0, costofitems=0;

int supplycosts[NUMSUPPLIES] = {1, 2, 20, 10};

char choice;

// Setup while loop for shopping
while(shopping == 1) {

// Print options
printf("You have %d gold pieces.\n", *funds);
printf("Available Supplies:\n");
printf("1. Food - 1 gold pieces\n");
printf("2. Clothes - 2 gold pieces\n");
printf("3. Ship Parts - 20 gold pieces\n");
printf("4. Shovels - 10 gold pieces\n");
printf("5. Leave Store\n");

// Get user input for their desired option.
// getch() masks the input to the console, getche()  prints the input to the screen,  getchar() only reads the input, we want getche().
choice=getche();
printf("\n");

if(choice == '1') {
    // Query user for how many of this item they'd like to buy
    printf("How many pounds of food would you like to buy?\n");
    scanf("%d",&numbought);
    // Calculate total cost of these items.
    costofitems = supplycosts[0]*numbought;

    // Can they afford the amount of items they asked for?
    if (*funds >= costofitems) {
        // If they can afford it, decrement funds & add supplies to their inventory
        *funds = *funds - (supplycosts[0]*numbought);
        supplies[0] = supplies[0] + numbought;
    }
    // If they can't afford the amount they asked for.
    else
        printf("Sorry, you cannot afford that many pounds of food.\n");


// Reset variables for later use
numbought=0;
costofitems=0;
}

if(choice=='2') {
    // Query user for how many of this item they'd like to buy
    printf("How many sets of clothes would you like to buy?\n");
    scanf("%d",&numbought);
    printf("\n");
    // Calculate total cost of these items.
    costofitems = supplycosts[1]*numbought;

    // Can they afford the amount of items they asked for?
    if (*funds >= costofitems) {
        // If they can afford it, decrement funds & add supplies to their inventory
        *funds = *funds - (supplycosts[1]*numbought);
        supplies[1] = supplies[1] + numbought;
    }
    // If they can't afford the amount they asked for.
    else
        printf("Sorry, you cannot afford that many sets of clothes.\n");


// Reset variables for later use
numbought=0;
costofitems=0;
}

if(choice=='3') {
    // Query user for how many of this item they'd like to buy
    printf("How many extra ship parts do you want to buy?\n");
    scanf("%d",&numbought);
    printf("\n");
    // Calculate total cost of these items.
    costofitems = supplycosts[2]*numbought;

    // Can they afford the amount of items they asked for?
    if (*funds >= costofitems) {
        // If they can afford it, decrement funds & add supplies to their inventory
        *funds = *funds - (supplycosts[2]*numbought);
        supplies[2] = supplies[2] + numbought;
    }
    // If they can't afford the amount they asked for.
    else
        printf("Sorry, you cannot afford that many ship parts.\n");


// Reset variables for later use
numbought=0;
costofitems=0;
}

if(choice=='4') {
    // Query user for how many of this item they'd like to buy
    printf("How many shovels do you want to buy?\n");
    scanf("%d",&numbought);
    printf("\n");
    // Calculate total cost of these items.
    costofitems = supplycosts[3]*numbought;

    // Can they afford the amount of items they asked for?
    if (*funds >= costofitems) {
        // If they can afford it, decrement funds & add supplies to their inventory
        *funds = *funds - (supplycosts[3]*numbought);
        supplies[3] = supplies[3] + numbought;
    }
    // If they can't afford the amount they asked for.
    else
        printf("Sorry, you cannot afford that many shovels.\n");


// Reset variables for later use
numbought=0;
costofitems=0;
}

if(choice=='5'){
    // Break while loop.
    shopping=0;
}
}

// Print remaining gold pieces after shopping is complete.
printf("You have %d gold pieces.\n", *funds);
return;
}

//Pre-conditions:  crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//                 supplies is an array of integers representing how many of each type the crew has
//                 funds represents how many gold pieces the crew has to spend
//                 traveled represents the total number of miles the ship has traveled from the beginning
//Post-conditions: none

//What to do in this function: Print a daily status report by telling the user how many miles have been
//  traveled.  Then, print the status of the crew by calling printstatus.  Print the funds and amount
//  of food that the ship has.  Then, let the user know how far they are from their next destination.
void dailyreport(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int funds, int traveled) {

// Calculate miles to next destination
int distancetodest, secondleg, thirdleg;
secondleg = CANARY + GRENADA;
thirdleg = CANARY + GRENADA + FINAL;

if (traveled <= CANARY)
    distancetodest = CANARY - traveled;
else if (traveled <= secondleg)
    distancetodest = secondleg - traveled;
else if (traveled <= thirdleg)
    distancetodest = thirdleg - traveled;

// Print the daily report
printf("You have traveled %d miles.\n", traveled);
printstatus(crewnames, crewstatus);
printf("You have %d gold pieces.\n", funds);
printf("You have %d pounds of food.\n", supplies[0]);
printf("You are %d miles from your next destination.\n", distancetodest);

return;
}

//Pre-conditions:  a and b are both integers
//Post-conditions: the larger value will be returned
int max(int a, int b) {

// Which value is greater?
if (a > b) {
    return a;
}
if (b >= a) {
    return b;
}
}

//Pre-conditions:  a and b are both integers
//Post-conditions: the smaller value will be returned
int min(int a, int b) {

// Which value is less?
if (a < b) {
    return a;
}
if (b <= a) {
    return b;
}
}

//Pre-conditions:  supplies is an array of integers representing how many of each type the crew has
//                 crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//                 days represents the current day
//Post-conditions: the user will select a number of days to rest for. update days to reflect this number
//                 there is a small chance an ill crew member will recover during rest days

//What to do in this function: ask the user how many days they would like to rest for.
//  Updates days to indicate that that many days has now passed.  Deduct 2 pounds of food
//  for each crew member for each day rested.

//  Generate a pseudorandom value that will be either 0 or 1.  Generate a second value
//  between 0 and the number of original crew members.  If the first number is a 1,
//  the crew member in the index of the second number may recover if they are sick.
//  If they are healthy or deceased, nothing happens.  If the first number is a 0,
//  nothing happens.
void rest(int supplies[NUMSUPPLIES], char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days) {

int daystorest=0;

// Ask the user how long they'd like to rest.
printf("How many days would you like to rest for?\n");
scanf("%d",&daystorest);
// Increment days counter.
*days = *days+daystorest;
// Consume supplies in days they rest.
supplies[0] = max(0, supplies[0] - (daystorest * (countcrew(crewstatus) * 2)));

int random_number1, random_number2;
// Calculate random number thats either 1 or 0
random_number1 = rand() % 1;
// Calculate random number thats between 1 and 4 inclusive
random_number2 = rand() % (NUMCREW-1);

// Follow the logic define above, and recover sick crew members if random numbers match certain values.
if (random_number1 == 1 && crewstatus[random_number2] != 0 && crewstatus[random_number2] != 2) {
        crewstatus[random_number2] = 2;
        printf("%s has recovered.", crewnames[random_number2]);
}

return;
}

//Pre-conditions:  none
//Post-conditions: returns the number of pounds of fish gained by the ship

//What to do in this function: Generate a pseudorandom value between 0 and 3, inclusive.
//  Multiply this number by 50 and tell the user how many fish were caught.  Return
//  this value.
int fish() {

// Calculate a random number between 0 and 3 inclusive
int random_number, num_fish;
random_number = rand() % 4;
num_fish = random_number * 50;
printf("Your crew lowers the nets and pulls up %d pounds of fish.\n", num_fish);

return num_fish;
}

//Pre-conditions:  crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//                 days represents the current day
//                 supplies is an array of integers representing how many of each type the crew has
//Post-conditions: the status of a crew member or supplies may be affected by a random event,
//                 some events cause the ship to be delayed a certain number of days

//What to do in this function: Generate a pseudorandom number between 0 and 9, inclusive.  If the user
//  has run out of food, tell the user they have no food and increase your number by 2.  This number cannot
//  exceed 9.

//  Numbers 0, 1, and 2 do not correspond with any events.
//  Numbers 3 and 4 correspond with "positive events"
//      on a 3 the user will gain between 1 and 4 ship parts determined randomly
//      on a 4 the user will gain between 10 and 60 pounds of food determined randomly
//      both events take 1 day
//  Number 5 means the user will lose between 5 and 55 pounds of food
//      this event takes 1 day
//  Number 6 means the ship is stuck in fog, which takes 1 day
//  Number 7 means the ship is in a storm, which takes 2 days
//  Number 8 means something on the ship has broken
//      check the number of extra ship parts the crew has
//      if they have at least one ship part, they can replace it and continue
//      this takes 1 day
//      if they have no extra parts, they must stop and repair
//      this takes 3 days
//  Number 9 indicates sickness.  Generate a random number between 0 and the original
//      number of crew members.  Check the status of that crew member: if they are healthy,
//      they now fall ill.  If they are already ill, they now perish.  If they are already
//      deceased, nothing happens.

//  For any days spent in this way, deduct 2 pounds of food per crew member per day.
void event(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days, int supplies[NUMSUPPLIES]) {

int random_number3, random_number4, random_number5, random_number6;
// Calculate a random number between 0 and 10 inclusive
random_number3 = rand() % 10;

// Is the user out of food?
if (supplies[0] == 0) {
    printf("You are out of food!\n");
    // Value can't exceed 9
    if (random_number3 < 8) {
    random_number3 = random_number3 + 2;
    }
}

// Good event (3)
if (random_number3 == 3) {
    random_number4 = (rand() % 4) +1;
    supplies[2] = supplies[2] + random_number4;
    printf("Another pirate ship pulls alongside and attacks!\n");
    printf("You fend them off and take %d extra ship parts.\n", random_number4);
    printf("You spend the day recovering.\n");
    // Increment days counter for rest day
    *days = *days + 1;
    // Decrement food for rest day
    supplies[0] = max(0, supplies[0] - ((countcrew(crewstatus) * 2)));
}

// Good event (4)
if (random_number3 == 4) {
    random_number4 = (rand() % 50) + 11;
    supplies[0] = supplies[0] + random_number4;
    printf("Another pirate ship pulls alongside and attacks!\n");
    printf("You fend them off and take %d pounds of their food.\n", random_number4);
    printf("You spend the day recovering.\n");
    //Increment days counter for rest day
    *days = *days + 1;
    // Decrement food for rest day
    supplies[0] = max(0, supplies[0] - ((countcrew(crewstatus) * 2)));
}

// Bad event (5)
if (random_number3 == 5) {
    random_number4 = (rand() % 50) + 6;
    supplies[0] = supplies[0] - random_number4;
    printf("Another pirate ship pulls alongside and attacks!\n");
    printf("They took %d pounds of food and you spend the day recovering.\n.", random_number4);
    // Increment days counter for rest day
    *days = *days + 1;
    // Decrement food for rest day
    supplies[0] = max(0, supplies[0] - ((countcrew(crewstatus) * 2)));
}

// Bad event (6)
if (random_number3 == 6) {
    printf("Fog surrounds your ship.  Drop anchor for one day.\n");
    // Increment days counter for rest day
    *days = *days + 1;
    // Decrement food for rest day
    supplies[0] = max(0, supplies[0] - ((countcrew(crewstatus) * 2)));
}

// Bad event (7)
if (random_number3 == 7) {
    printf("An ocean storm batters your ship.  Drop anchor for two days.\n");
    // Increment days counter for rest days
    *days = *days + 2;
    // Decrement food for rest days
    supplies[0] = max(0, supplies[0] - (2 * (countcrew(crewstatus) * 2)));
}

// Bad event (8)
if (random_number3 == 8) {
    //supplies[0] = supplies[0] - random_number4;
    printf("A part of your ship has broken!\n");

    // Do they have extra ship parts?
    if (supplies[2] >= 1) {
        // Decrement extra ship parts by 1
        supplies[2] = supplies[2] - 1;
        printf("You replace the broken part. It takes one day.\n");
        // Increment days counter for rest day
        *days = *days + 1;
        // Decrement food for rest day
        supplies[0] = max(0, supplies[0] - ((countcrew(crewstatus) * 2)));

    }

    // If they don't have extra ship parts.
    else if (supplies[2] == 0) {
        printf("You have no replacement parts. It takes three days to repair.\n");
        // Increment days counter for rest days
        *days = *days + 3;
        // Decrement food for rest days
        supplies[0] = max(0, supplies[0] - (3 * (countcrew(crewstatus) * 2)));
    }
}

// Bad event (9)
if (random_number3 == 9) {

    // NUMCREW-1 to make our number align with the crew members position in the array
    random_number5 = rand() % (NUMCREW-1);

    // If they are healthy, make them ill
    if (crewstatus[random_number5] == 2) {
            crewstatus[random_number5] = 1;
            printf("%s has fallen ill.\n", crewnames[random_number5]);

    }

    // If they are ill, they perish.
    else if (crewstatus[random_number5] == 1) {
            crewstatus[random_number5] = 0;
            printf("%s has died.\n", crewnames[random_number5]);

    }
}
return;
}
