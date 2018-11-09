#include <avr/io.h>
#include <stdio.h>
#include "global_defines.h"
#include "util/delay.h"
#include <stdint.h>
#include "uart.h"
#include "snake_game.h"
#include <stdlib.h>
#include "breadboard_input.h"
#include "oled_sram.h"



// Map dimensions
int8_t mapwidth = 8;
int8_t mapheight = 8;

int8_t size = 100;

// The tile values for the map
int8_t map[100];

// Snake head details
int8_t headxpos;
int8_t headypos;
int8_t direction =0;

// Amount of food the snake has (How long the body is)
int8_t food = 3;

// Determine if game is running
int8_t running = 0;



void snake_run(){
    // Initialize the map
    initMap();
    running = 1;
    while (running) {
        // If a key is pressed
        // Change to direction determined by key pressed
        snake_changeDirection();
        // Upate the map
        snake_update();

        // Clear the screen
        clearScreen();

        // Print the map
        //printMap();

        //print map oled
        printMap_sram();

        // wait 0.5 seconds
        _delay_ms(2000);
}
    // Print out game over text
    USART_printf("game over, score is %d \n",food);
}


// Changes snake direction from input
void snake_changeDirection() {

    struct Joystick_positions position = joystick_read_positions();
    int new_dir = 0;

    if(position.x > 50){
      new_dir = 1;
    }
    else if(position.x < -50){
      new_dir = 0;
    }
    else{
        return;
    }

    //new dir = get_button_value
    USART_printf("newdir position %d %d\n",new_dir,position.x);
    if (new_dir == 1 && direction < 3){
      direction += 1;
      //printf("direction %d\n",direction);
      return;
    }
    else if(new_dir == 1){
      direction = 0;
      //printf("direction %d\n",direction);
      return;
    }
    if(new_dir == 0 && direction > 0){
      direction -= 1;
    }else{
      direction = 3;
    }
    //printf("direction %d\n",direction);
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
             USART_printf("%c",getMapValue(map[x + y * mapwidth]));
        }
        // Ends the line for next x value
        USART_printf("\n");
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
    return ' ';
}


// Updates the map
void snake_update() {
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
        running = 0;
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
    return;
    // Clear the screen
    //system("cls");
}


void printMap_sram()
{
    for (int x = 0; x < mapwidth; ++x) {
        for (int y = 0; y < mapheight; ++y) {
            // Prints the value at current x,y location
             oled_sram_put_char(getMapValue(map[x + y * mapwidth]));

             USART_printf("%c",getMapValue(map[x + y * mapwidth]));
        }
        // Ends the line for next x value
        oled_sram_print("\n");
        USART_printf("\n");

    }
    oled_sram_update();
}
