//code inspired from https://codereview.stackexchange.com/questions/66481/snake-game-in-c

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

struct Snake_game snake1 = {
    .index = 1,
    .mapwidth = 8,
    .mapheight = 8,
    .size = 64,
    .direction = 0,
    .food = 3,
    .running = 0
};

struct Snake_game snake2 = {
    .index = 2,
    .mapwidth = 8,
    .mapheight = 8,
    .size = 64,
    .direction = 0,
    .food = 3,
    .running = 0
};

void snake_play_both(){
    snake1.mapheight = 8;
    snake1.mapwidth = 8;
    snake1.size = 64;
    snake_init(&snake1);
    snake_init(&snake2);
    uint8_t i = 0;
    while (snake1.running ||snake2.running){
        if (snake1.running && i%2 == 0){
            snake_tick(&snake1);
        }
        if (snake2.running){
            snake_tick(&snake2);
        }
        _delay_ms(1000);
        i++;
    }
}

void snake_init(struct Snake_game* snake){
    // Initialize the map
    snake->food = 3;
    initMap(snake);
    snake->running = 1;
}

void snake_tick(struct Snake_game* snake){
        // If a key is pressed
        // Change to direction determined by key pressed
        switch(snake->index){
            case 1:
                snake1_changeDirection();
                break;
            case 2:
                snake2_changeDirection();
                break;
        }
        // Upate the map
        snake_update(snake);

        // Clear the screen
        clearScreen();

        // Print the map
        //printMap();

        //print map oled
        switch(snake->index){
            case 1:
                snake1_printMap_oled();
                break;
            case 2:
                snake2_printMap_oled();
                break;
        }

}

uint8_t snake_run(uint8_t difficulty){
    // Initialize the map
    snake1.mapheight = 16;
    snake1.mapwidth = 8;
    snake1.size = 128;
    snake1.food = 3;
    initMap(&snake1);
    snake1.running = 1;
    while (snake1.running) {
        // If a key is pressed
        // Change to direction determined by key pressed
        snake1_changeDirection();

        // Upate the map
        snake_update(&snake1);


        //print map oled
        snake1_printMap_oled();

        // wait 0.5 seconds
        switch (difficulty) {
            case 3:
            _delay_ms(200);
            break;
            case 2:
            _delay_ms(500);
            break;
            case 1:
            _delay_ms(1000);
            break;
            default:
            _delay_ms(1000);

        }

}
    // Print out game over text

    return snake1.food;
}


// Changes snake direction from input
void snake1_changeDirection() {

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
    if (new_dir == 1 && snake1.direction < 3){
      snake1.direction += 1;
      //printf("direction %d\n",direction);
      return;
    }
    else if(new_dir == 1){
      snake1.direction = 0;
      //printf("direction %d\n",direction);
      return;
    }
    if(new_dir == 0 && snake1.direction > 0){
      snake1.direction -= 1;
    }else{
      snake1.direction = 3;
    }
    //printf("direction %d\n",direction);
}
void snake2_changeDirection() {
    int new_dir = 0;

    if(right_touch_button_read()){
      new_dir = 1;
  }
    else if(left_touch_button_read()){
      new_dir = 0;
  }
    else{
        return;
    }

    //new dir = get_button_value
    if (new_dir == 1 && snake2.direction < 3){
      snake2.direction += 1;
      //printf("direction %d\n",direction);
      return;
    }
    else if(new_dir == 1){
      snake2.direction = 0;
      //printf("direction %d\n",direction);
      return;
  }
    if(new_dir == 0 && snake2.direction > 0){
      snake2.direction -= 1;
    }else{
      snake2.direction = 3;
    }
    //printf("direction %d\n",direction);
}

// Initializes map
void initMap(struct Snake_game* snake)
{
    //clear map before init
    for (int i = 0; i < snake->mapwidth*snake->mapheight; i++){
      snake->map[i] = 0;
    }

    // Places the initial head location in middle of map
    snake->headxpos = snake->mapwidth / 2;
    snake->headypos = snake->mapheight / 2;
    snake->map[snake->headxpos + snake->headypos * snake->mapwidth] = 1;
    //USART_printf("snakeindex = %d\n",snake->index);

    // Places top and bottom walls
    for (int x = 0; x < snake->mapwidth; ++x) {
        snake->map[x] = -1;
        snake->map[x + (snake->mapheight - 1) * snake->mapwidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < snake->mapheight; y++) {
        snake->map[0 + y * snake->mapwidth] = -1;
        snake->map[(snake->mapwidth - 1) + y * snake->mapwidth] = -1;
    }

    // Generates first food
    generateFood(snake);
}

void printMap()
{/*
    for (int x = 0; x < snake1.mapwidth; ++x) {
        for (int y = 0; y < snake1.mapheight; ++y) {
            // Prints the value at current x,y location
             USART_printf("%c",getMapValue(snake1.map[x + y * snake1.mapwidth]));
        }
        // Ends the line for next x value
        USART_printf("\n");
    }*/
    return;
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
    //USART_printf("getValue = %d\n",value);
    // Returns a part of snake body
    if (value > 0){
        return 'o';
    }

    switch (value) {
        // Return wall
    case -1: return 'X';
        // Return food
    case -2: return 'O';
    }
    return ' ';
}


// Updates the map
void snake_update(struct Snake_game* snake) {
    // Move in direction indicated
    switch (snake->direction) {
    case 0: move(-1, 0, snake);
        break;
    case 1: move(0, 1, snake);
        break;
    case 2: move(1, 0, snake);
        break;
    case 3: move(0, -1, snake);
        break;
    }

    // Reduce snake values on map by 1
    for (int i = 0; i < snake->size; i++) {
        if (snake->map[i] > 0) snake->map[i]--;


    }
}



// Moves snake head to new location
void move(int dx, int dy, struct Snake_game* snake) {
    // determine new head position
    int newx = snake->headxpos + dx;
    int newy = snake->headypos + dy;

    // Check if there is food at location
    if (snake->map[newx + newy * snake->mapwidth] == -2) {
        // Increase food value (body length)
        snake->food++;

        // Generate new food on map
        generateFood(snake);
    }

    // Check location is free
    else if (snake->map[newx + newy * snake->mapwidth] != 0) {
        snake->running = 0;
    }

    // Move head to new location
    snake->headxpos = newx;
    snake->headypos = newy;
    snake->map[snake->headxpos + snake->headypos * snake->mapwidth] = snake->food + 1;

}

// Generates new food on map
void generateFood(struct Snake_game* snake) {
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the map
        x = rand() % (snake->mapwidth - 2) + 1;
        y = rand() % (snake->mapheight - 2) + 1;

        // If location is not free try again
    } while (snake->map[x + y * snake->mapwidth] != 0);

    // Place new food
    snake->map[x + y * snake->mapwidth] = -2;
}


// Clears screen
void clearScreen() {
    return;
    // Clear the screen
    //system("cls");
}


void snake1_printMap_oled()
{
    for (int x = 0; x < snake1.mapwidth; ++x) {
        for (int y = 0; y < snake1.mapheight; ++y) {
            // Prints the value at current x,y location
             oled_sram_put_char(getMapValue(snake1.map[x + y * snake1.mapwidth]));

        }
        // Ends the line for next x value
        oled_sram_put_char('\n');

    }

/*
    for (int x = 0; x < mapwidth; ++x) {
        oled_goto_column(64);
        for (int y = 0; y < mapheight; ++y) {
            // Prints the value at current x,y location
             oled_sram_put_char(getMapValue(map[x + y * mapwidth]));

        }
        // Ends the line for next x value
        oled_sram_put_char('\n');

    }
*/
    oled_sram_update();
}
void snake2_printMap_oled()
{
    //oled_sram_clear_screen();
    for (int x = 0; x < snake2.mapwidth; ++x) {
        oled_goto_column(64);
        for (int y = 0; y < snake2.mapheight; ++y) {
            // Prints the value at current x,y location
             oled_sram_put_char(getMapValue(snake2.map[x + y * snake2.mapwidth]));

        }
        // Ends the line for next x value
        oled_sram_put_char('\n');

    }
    oled_sram_update();
}
