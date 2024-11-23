#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <termios.h> 
#include <fcntl.h>   
#include "lib/snake.h"

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main(void)
{
    Snake snake;
    int foodX, foodY, length;
    int dx = 1, dy = 0;
    int gameOver = 0;
    int score = 0;

    initializeGame(&snake, &foodX, &foodY, &length);

    while (!gameOver)
    {
        if (kbhit())
        {
            char ch = getchar();
            switch (ch)
            {
            case 'w': // Cima
                dx = 0;
                dy = -1;
                break;
            case 's': // Baixo
                dx = 0;
                dy = 1;
                break;
            case 'a': // Esquerda
                dx = -1;
                dy = 0;
                break;
            case 'd': // Direita
                dx = 1;
                dy = 0;
                break;
            case 'q': // Sair
                gameOver = 1;
                break;
            }
        }

        for (int i = length; i > 0; i--)
        {
            snake.x[i] = snake.x[i - 1];
            snake.y[i] = snake.y[i - 1];
        }

        snake.x[0] += dx;
        snake.y[0] += dy;

        if (snake.x[0] < 0 || snake.x[0] >= WIDTH || snake.y[0] < 0 || snake.y[0] >= HEIGHT)
        {
            gameOver = 1;
        }

        for (int i = 1; i < length; i++)
        {
            if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
            {
                gameOver = 1;
                break;
            }
        }

        if (snake.x[0] == foodX && snake.y[0] == foodY)
        {
            if (length < MAX_SNAKE_LENGTH)
            {
                length++;
                score++;
            }
            foodX = rand() % (WIDTH - 2) + 1;
            foodY = rand() % (HEIGHT - 2) + 1;
        }

        printGame(&snake, length, foodX, foodY, score);
        usleep(100000); 
    }

    printf("Game Over! Seu score: %d\n", score);
    return 0;
}
