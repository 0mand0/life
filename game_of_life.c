#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void draw(void *u, int w, int h)
{
    char (*world)[w] = u;
    printf("\033[H");
    //printf("\033[32;40m");
    printf("\033[92;40m");
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf(world[i][j] ? "@" : ".");
        }
        printf("\n");
    }
    printf("\033[93;40m");
    printf("Game of life 80X30\n");
    printf("\033[31;40m");
    printf("Close press CTRL + C\n");
}

void evolution(void *u, int w, int h)
{
    char (*world)[w] = u;
    char new[h][w];
    //
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int lives = 0;
            for (int xd = x - 1; xd <= x + 1; xd++)
            {
                for (int yd = y - 1; yd <= y + 1; yd++)
                {
                    if (world[(yd + h) % h][(xd + w) % w])
                    {
                        lives++;
                    }
                }
            }
            if (world[y][x])
            {
                lives--;
            }
            new[y][x] = (lives == 3 || (lives == 2 && world[y][x]));
            /*
            * !!! Delete this block !!!
            * 
            if (lives == 3)
            {
                new[y][x] = 1;
            }
            else if (lives == 2 && world[y][x] == 1)
            {
                new[y][x] = 1;
            }
            else
            {
                new[y][x] = 0;
            }
            *
            *
            */
        }
    }
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            world[y][x] = new[y][x];
        }
    }
}

int main()
{
    int w = 80;
    int h = 30;
    char world[w][h];
    srand(time(0));
    printf("\033[H");
    //
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            world[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
        }
    }
    while (1)
    {
        draw(world, w, h);
        evolution(world, w, h);
        usleep(1000000);
    }
    return 0;
}