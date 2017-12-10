/* Nolen Johnson
* COP3223C-17Fall 0R04 - Project 5: SettingSail
* Calculates optimal time to set sail based on a file containing temperature data per month
*/


// Included Libraries
#include <stdio.h>
#include <stdlib.h>

// No Constants to declare

// Begin main function
int main()
{

    // Declare file pointer
    FILE * ifp;

    // Store this as a char
    char filename[30];
    // Store these as Integers because the input has been dictated by the assignment
    int best_month = 0, best_percent = 0, numDays, days_in_month, month=0, mintemp, maxtemp, i=0;
    // Store these as floats instead of an integers because we are looking for an output accurate to 2 decimal places
    float day_temp, days_in_range, percent;

    // Pirate Introduction 5
    printf("ARGH Captain, I'm here to help ya figure out when be best to set sail for the Caribbean!\n\n");
    printf("Tell me about your crews preferred temperature for sailing:\n\n");

    // Query user for data
    printf("What is the coldest temperature they can sail in?\n");
    scanf("%d", &mintemp);
    printf("What is the hottest temperature they can sail in?\n");
    scanf("%d", &maxtemp);

    printf("Please enter the name of the weather data file:\n");
    scanf("%s", filename);

    // Initialize the file pointer
    ifp = fopen(filename, "r");
    // Is the file valid?/Does it exist?/Do we have permissions to view it?
    if(!ifp)
    {
        printf("\n Unable to open the file");
        return 0;
    }

    // Scan our files first line into a variable to dictate the number of days in the given month
        while( fscanf(ifp, "%d", &numDays) > 0 )
    {
        month = month + 1;
        // Reset this variable each loop through to prevent adding across months
        days_in_range = 0;
        // Increment the day of the month
        for (i=0; i<numDays; i++)
        {
            // Scan the temperature data in based on how many days are in the month
            fscanf(ifp, "%f", &day_temp);

            // Determines if the temperature is within range
            if ((mintemp <= day_temp) && ( maxtemp >= day_temp))
            {
                // If it is in the range, increment the total number of days that were in range in that given month
                days_in_range=days_in_range+1;
            }
        }

        // Calculate the percentage of day that were in range
        percent = (days_in_range / numDays) * 100;

        // Figure out which month was the best to leave in
        if(best_percent < percent)
        {
            best_percent = percent;
            best_month = month;
        }

        // Let the user know how many days were in range
        printf("\nMonth %d: %.01f percent of days in range.", month, percent);

    }

    // Close the file
    fclose(ifp);

    printf("\n\nYou should leave for the Caribbean in Month %d!\n", best_month);

    // Exit the program
    return 0;

} // End of Main
