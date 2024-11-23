#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include "lib/snake.h"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

void initializeGame(Snake *snake, int *foodX, int *foodY, int *length)
{
    snake->x[0] = WIDTH / 2;
    snake->y[0] = HEIGHT / 2;
    *length = 1;

    *foodX = rand() % (WIDTH - 2) + 1;
    *foodY = rand() % (HEIGHT - 2) + 1;
}

void printGame(Snake *snake, int length, int foodX, int foodY, int score)
{
    clearScreen();

    for (int x = 0; x < WIDTH + 2; x++)
    {
        printf("#");
    }
    printf("\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        printf("#");
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == snake->x[0] && y == snake->y[0])
            {
                printf("O");
            }
            else if (x == foodX && y == foodY)
            {
                printf("*");
            }
            else
            {
                int isBody = 0;
                for (int i = 1; i < length; i++)
                {
                    if (x == snake->x[i] && y == snake->y[i])
                    {
                        printf("o");
                        isBody = 1;
                        break;
                    }
                }
                if (!isBody)
                {
                    printf(" ");
                }
            }
        }
        printf("#\n");
    }

    for (int x = 0; x < WIDTH + 2; x++)
    {
        printf("#");
    }
    printf("\n");

    printf("Score: %d\n", score);
}
