#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH 20
#define HEIGHT 10
#define MAX_SNAKE_LENGTH 100

typedef struct
{
    int x[MAX_SNAKE_LENGTH];
    int y[MAX_SNAKE_LENGTH];
} Snake;

void clearScreen();
void initializeGame(Snake *snake, int *foodX, int *foodY, int *length);
void printGame(Snake *snake, int length, int foodX, int foodY, int score);

#endif
