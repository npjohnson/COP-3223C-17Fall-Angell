/* Nolen Johnson
* COP3223C-17Fall 0R04 - Project 3: PirateGear - 09/24/17
* Acts as a store for pirates, keeps track of the numbers of used/new gear, the price per item, total, and average price per item of a users shopping cart.
*/

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// This is included as it adds additional get-char related functions
#include <conio.h>

//Define Constants
#define USED_GEAR_PRICE 5
#define NEW_GEAR_PRICE 15

//main function
int main(){

// Define choice as a char so as not to treat it as a number, but as a choice
char choice;
// Define this as a char, and set it to 1 until we set it to 0 to exit
char getting_gear=1;
// We use double instead of an integer because we are looking for an output accurate to 2 decimal places, and a double can store more data than a float
double new_gear_quan=0,used_gear_quan=0,total_gear_quan,subtotal1=0,subtotal2=0,total_new_gear_quan=0,total_used_gear_quan=0,total,avg;

// Cutesy Pirate Introduction 3
printf("ARGH, welcome to me pirate shop! \n");

// Set up a loop
while(getting_gear == 1)
{
printf("Enter choice\n");
printf("1. Buy New Gear.\n");
printf("2. Buy Used Gear.\n");
printf("3. Quit.\n");
// getch() masks the input to the console, as opposed to getche() which prints the input to the screen, or getchar() which only reads the input
choice=getch();

// Choice 1
if(choice == '1') {
    printf("How many pieces of new gear would you like to buy? \n");
    scanf("%lf",&new_gear_quan);
    subtotal1=subtotal1+(NEW_GEAR_PRICE*new_gear_quan);
    total_new_gear_quan = total_new_gear_quan + new_gear_quan;
    printf("Sub total: New Gear=%0.0lf\n",subtotal1);
    //getch() doesn't echo the input to the screen
    getch();
}

//Choice 2
if(choice == '2'){
    printf("How many pieces of used gear would you like to buy? \n");
    scanf("%lf",&used_gear_quan);
    subtotal2=subtotal2+(USED_GEAR_PRICE*used_gear_quan);
    total_used_gear_quan = total_used_gear_quan + used_gear_quan;
    printf("Sub total: Used Gear=%0.0lf\n",subtotal2);
    //getch() doesn't echo the input to the screen
    getch();
}

// Choice 3
if(choice == '3') {
    getting_gear=0; // Break the loop
}

// Check for Invalid Choices, for some reason, checking if choice != the values resulted in the invalid choice message appearing at strange times
if(choice == '1' || choice == '2' || choice == '3' ) {}
else {
printf("Sorry, %c is not a valid choice. \n",choice);
}

}

// Choice 3 prints the totals/averages and exits, but only after the loop is broken
// TODO: fix the extra decimals placed in the console output by the use of a double instead of an integer
// I left it as a double because as an integer, our averages didn't come out right
if(choice == '3', getting_gear == 0) {
    total=subtotal1+subtotal2;
    total_gear_quan=new_gear_quan+used_gear_quan;
    avg=(subtotal1 + subtotal2) / total_gear_quan;
    printf("Your total cost is %0.0lf gold pieces. \n", total);
    printf("You obtained %0.0lf pieces of new gear and %0.0lf pieces of used gear. \n", total_new_gear_quan, total_used_gear_quan);
    printf("The average cost per piece of gear is %.02lf pieces of gold. \n",avg);
    exit(0);
}

}
