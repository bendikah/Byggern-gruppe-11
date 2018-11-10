#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include <stdint.h>

struct Snake_game {
    // Index to separate the different snakes
    int8_t index;
    // Map dimensions
    int8_t mapwidth;
    int8_t mapheight;
    uint8_t size;

    // The tile values for the map
    int8_t map[128];

    // Snake head details
    int8_t headxpos;
    int8_t headypos;
    int8_t direction;

    // Amount of food the snake has (How long the body is)
    int8_t food;

    // Determine if game is running
    int8_t running;
};

extern struct Snake_game snake1;
extern struct Snake_game snake2;

uint8_t snake_run(uint8_t difficulty);
void printMap();
void snake1_printMap_oled();
void snake2_printMap_oled();
void initMap(struct Snake_game* snake);
void move(int dx, int dy, struct Snake_game* snake);
void snake_update(struct Snake_game* snake);
void snake1_changeDirection();
void snake2_changeDirection();
void clearScreen();
void generateFood(struct Snake_game* snake);

char getMapValue(int value);
//void printMap_sram();

void snake_play_both();

#endif
