/* Nolen Johnson
* COP3223C-17Fall 0R04 - Project 4: LandingCrew - 10/01/17
* Calculates per day averages of specific crew's
*/

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//No Constants to declare

//Begin main function
int main(){

// Store this as a char, and set it to 1 until we set it to 0 to exit
char observing=1;
// Store these as Integers because the input has been dictated by the assignment
int days_observing, days_observing_temp=1, trips_per_day=1,trips_per_day_temp=1;
// Store these as doubles instead of an integers because we are looking for an output accurate to 2 decimal places, and a double can store more data than a float
double length_of_trip=0,length_of_trip_temp=0,total_length_of_trips=0,avg;

//Cutesy Pirate Introduction 3
printf("How many days will you observe the landing crew? \n");
scanf("%i", &days_observing);

// Make sure input is a valid integer larger than one
if (1 <= days_observing) {

    // Loop 1 - Dictates whether the user is in a state of observing the landing crews or not.
    while(observing == 1) {

        // Loop 2 - Takes user input of the number of days they'll be observing, and increments up until the "temp" variable matches the user input.
        while(days_observing >= days_observing_temp) {

            // Reset trips per day for every new day.
            trips_per_day_temp=0;
            printf("How many trips were completed in day #%i? \n", days_observing_temp);
            scanf("%i", &trips_per_day);
            days_observing_temp=days_observing_temp+1;

            // Loop 3 - Takes user input of trips per day, and increments up until the "temp" variable matches the user input.
            while(trips_per_day > trips_per_day_temp) {
                trips_per_day_temp=trips_per_day_temp+1;
                printf("How long was trip #%i? \n", trips_per_day_temp);
                scanf("%lf", &length_of_trip);

                // Because we are in a loop, we can't store individual lengths of trip per day, so we store them in a mass "total_" variable.
                total_length_of_trips=total_length_of_trips+length_of_trip;

            } // End Loop 3

        // Total length of trips is equal to the sum of each individual trip, then we divide by the total number of trips in the day.
        avg=total_length_of_trips/trips_per_day;
        printf("Day #%i: The average time was %.03lf. \n", days_observing_temp, avg);

        // Reset total length of trips for every new day.
        total_length_of_trips=0;

        } // End Loop 2
    observing=0;

    } // End Loop 1
    exit(0);

}

// Check for input of zero
else if (days_observing == 0) {
    printf("You aren't observing, goodbye.");
    exit(0); }

// Check for invalid input
// TODO: This detects certain inputs, but for example, inputting "test" has strange and unexplainable outputs (potentially due to declaring days_observing as an integer?)
else {
    printf("Invalid Input Detected.");
    exit(0);}

} //End of Main
