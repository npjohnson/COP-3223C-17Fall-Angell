#include <stdio.h>
#include <stdlib.h>

#define N_PIRATES 4
#define N_HOURS 8
#define S_MAP 9

struct map {
   int sand;
   int treasure;
};

struct pirate {
      int dig;
      int carry;
};

// Reads the map into an array
void read_map(FILE *fd, struct map island[S_MAP]) {
    int sand, treasure;
    int i, j;
    for (i = 0; i < S_MAP; i++) {
               fscanf(fd, "%d", &island[i].sand);
               fscanf(fd, "%d", &island[i].treasure);
        }
    }

// Print the map
void print_map(struct map island[S_MAP]) {
      int i, j;
    for (i = 0; i < S_MAP; i++) {
                // We need to
               if (island[i].sand > 0) {
                   if (i<=2) {
                   printf("%ds\t ", island[i].sand);
                   }
                   if (i>2 && i<=5) {
                   printf("%ds\t ", island[i].sand);
                   }
                    if (i>5 && i<=8) {
                   printf("%ds\t ", island[i].sand);
                   }
                    if (i==2 || i==5 || i==8) {
                   printf("\n");
                   }

               } else if (island[i].treasure > 0) {
                      printf("%dT ", island[i].treasure);
               } else {
                      printf("-\t ");
               }
        }
        printf("\n");
    }

// Manage the pirates digging and carrying
void move_pirate(struct map island[S_MAP], struct pirate one, int i, int j) {
    // Has this been cleared out already?
    if (island[i].sand == 0 && island[i].treasure == 0) {
        printf("This section has already been cleared.\n");
    }
    // Is there sand left?
    if (island[i].sand > 0) {
        int to_dig = min(island[i].sand, one.dig);

        one.dig -= to_dig;

        if (island[i].sand == 0) {
             printf("You have removed all of the sand from this section.\n");
        } else {
             printf("You have removed some of the sand from this section.\n");
        }
    }

    if (island[j].treasure > 0) {
        int to_carry = min(island[j].treasure, one.carry);
        island[j].treasure -= to_carry;
        one.carry -= to_carry;

        if (island[j].sand == 0) {
             printf("You take all of the treasure back to the ship.\n");
        } else {
             printf("You take some of the treasure back to the ship.\n");
        }
   }
}

// Keep track of the treasure count in case they don't get it all
int count_treasure(struct map island[S_MAP]) {
    int i,j,total = 0;
    for (i = 0; i < S_MAP; i++) {
               total += island[i].treasure;
    }
    return total;
}

// Read the crew into an array
int read_crew(FILE *fd, struct pirate pirates_data[S_MAP]) {
        int i, j;
        for (i=0; i<N_PIRATES; i++) {
        // Traverse the file
        fscanf(fd, "%d", &pirates_data[i].dig);
        fscanf(fd, "%d", &pirates_data[i].carry);
        }

}


// Print out the crews abilities
void print_crew(struct pirate pirates_data[S_MAP]) {
        int i;
        printf("Crew:   Dig:    Carry:\n");

        // Traverse the array, printing their values
        for (i=0; i<N_PIRATES; i++){
            printf("%d\t%d\t%d\n", i+1, pirates_data[i].dig, pirates_data[i].carry);
            }

        printf("\n");
}

int max(int a, int b) {

// Which value is greater?
if (a > b) {
    return a;
}
if (b >= a) {
    return b;
}
}

int min(int a, int b) {

// Which value is less?
if (a < b) {
    return a;
}
if (b <= a) {
    return b;
}
}

int main() {
    // Declare your variables here
    int i,j;
    int time;
    int n, hours_left=8;
    int current_treasure = 1;
    char filename[30] = {0}; // {0} will initialize/zero the array
    FILE *fd  = NULL; // It's good to initialze the pointer as null
    /* I use fd as the file descripter pointer,
       helpful for remembering what the pointer is
       */


    printf("You have arrived at Treasure Island!\n");

    printf("What is the name of your map?\n");
    fflush(stdin); // We flush the stdin buffer, just mashing keys before scanf can fill the stdin buf with junk
    scanf("%s", filename);
    printf("\n");

// Initialize the file pointer
    fd = fopen(filename, "r+");
    // Is the file valid?/Does it exist?/Do we have permissions to view it?
    if (!fd) {
        printf("\n Unable to open the file\n");
        return -1;
    }

    // declare structs and set to 0
    struct map island[S_MAP] = {0};
    read_map(fd, island);

    struct pirate pirates_data[S_MAP] = {0};
    read_crew(fd, pirates_data);

    int start_treasure = count_treasure(island);

    for (time = 0; time < N_HOURS && current_treasure; time++) {
    printf("You have %d hours left to dig up the treasure.\n", hours_left);

    for (n = 0; n < N_PIRATES && current_treasure; n++) {

        print_crew(pirates_data);

            printf("Where would you like to send crew member %d?\n", n + 1);
            printf("\n");
            scanf("%d %d", &i, &j);
              i--;
              j--;
              move_pirate(island, pirates_data[n], i, j);
              current_treasure = count_treasure(island);

              print_map(island);
              if (current_treasure == 0) {
                    printf("All of the pirate's treasure belongs to you!\n");
              }
       }
        hours_left--;
    }

    if (time == 0) {
           printf("You are forced to evacuate the island.\n");
           printf("You have claimed %d pieces of the pirate's treasure!\n", start_treasure - current_treasure);
    }
    print_map(island);
    return 0;
}
