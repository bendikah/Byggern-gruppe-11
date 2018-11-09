#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

void snake_run();
void printMap();
void initMap();
void move(int dx, int dy);
void snake_update();
void snake_changeDirection();
void clearScreen();
void generateFood();

char getMapValue(int value);
//void printMap_sram();

#endif
