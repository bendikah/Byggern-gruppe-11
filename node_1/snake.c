#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection();
void clearScreen();
void generateFood();

char getMapValue(int value);

// Map dimensions
const int mapwidth = 10;
const int mapheight = 10;

const int size = 100;

// The tile values for the map
int map[100];

// Snake head details
int headxpos;
int headypos;
int direction =0;

// Amount of food the snake has (How long the body is)
int food = 3;

// Determine if game is running
bool running;

int main()
{
    //her må vi sette vanskelighetsgrad eg hvor ofte det oppdateres..
    run();
    return 0;
}

// Main game function
void run()
{
    // Initialize the map
    initMap();
    running = true;
    while (running) {
        // If a key is pressed
        // Change to direction determined by key pressed
        changeDirection();
        // Upate the map
        update();

        // Clear the screen
        clearScreen();

        // Print the map
        printMap();

        // wait 0.5 seconds
        sleep(1);


    }

    // Print out game over text
    printf("game over, score is %d \n",food);

    // Stop console from closing instantly
}


// Changes snake direction from input
void changeDirection() {
    char number[1];
    int new_dir = 0;
    printf("Type in a number \n");
    scanf("%s", number);
    if(number[0] == 'a'){
      new_dir = 1;
    }
    else if(number[0] =='s'){
      new_dir = 0;
    }

    //new dir = get_button_value
    printf("newdir %d\n",new_dir);
    if (new_dir == 1 && direction < 3){
      direction += 1;
      printf("direction %d\n",direction);
      return;
    }
    else if(new_dir == 1){
      direction = 0;
      printf("direction %d\n",direction);
      return;
    }
    if(new_dir == 0 && direction > 0){
      direction -= 1;
    }else{
      direction = 3;
    }
    printf("direction %d\n",direction);
}

// Initializes map
void initMap()
{
    // Places the initual head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth] = 1;

    // Places top and bottom walls
    for (int x = 0; x < mapwidth; ++x) {
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < mapheight; y++) {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // Generates first food
    generateFood();
}

void printMap()
{
    for (int x = 0; x < mapwidth; ++x) {
        for (int y = 0; y < mapheight; ++y) {
            // Prints the value at current x,y location
             printf("%c",getMapValue(map[x + y * mapwidth]));
        }
        // Ends the line for next x value
        printf("\n");
    }
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
    // Returns a part of snake body
    if (value > 0) return 'o';

    switch (value) {
        // Return wall
    case -1: return 'X';
        // Return food
    case -2: return 'O';
    }
}


// Updates the map
void update() {
    // Move in direction indicated
    switch (direction) {
    case 0: move(-1, 0);
        break;
    case 1: move(0, 1);
        break;
    case 2: move(1, 0);
        break;
    case 3: move(0, -1);
        break;
    }

    // Reduce snake values on map by 1
    for (int i = 0; i < size; i++) {
        if (map[i] > 0) map[i]--;
    }
}



// Moves snake head to new location
void move(int dx, int dy) {
    // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Check if there is food at location
    if (map[newx + newy * mapwidth] == -2) {
        // Increase food value (body length)
        food++;

        // Generate new food on map
        generateFood();
    }

    // Check location is free
    else if (map[newx + newy * mapwidth] != 0) {
        running = false;
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth] = food + 1;

}

// Generates new food on map
void generateFood() {
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the map
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;

        // If location is not free try again
    } while (map[x + y * mapwidth] != 0);

    // Place new food
    map[x + y * mapwidth] = -2;
}


// Clears screen
void clearScreen() {
    // Clear the screen
    system("cls");
}
