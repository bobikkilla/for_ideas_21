#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_X 80
#define MAX_Y 25

void draw(void *u, int w, int h);
void evolve(void *u, int w, int h);
void delay(int milli_seconds);
void game(int w, int h);

int main() {
    game(MAX_X, MAX_Y);
    return 0;
}

void draw(void *u, int w, int h) {
    int(*univ)[w] = u;
    printf("\033[H");
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf(univ[y][x] ? "@" : " ");
        }
        printf("\033[E");
    }
    fflush(stdout);
}

void evolve(void *u, int w, int h) {
    unsigned(*univ)[w] = u;
    unsigned new[h][w];

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            int n = 0;
            for (int y1 = y - 1; y1 <= y + 1; y1++)
                for (int x1 = x - 1; x1 <= x + 1; x1++)
                    if (univ[(y1 + h) % h][(x1 + w) % w]) n++;
            if (univ[y][x]) n--;
            new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
        }
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) univ[y][x] = new[y][x];
}

void delay(int milli_seconds) {
    clock_t micro_seconds = milli_seconds * 1000;
    clock_t start_time = clock();

    while ((clock() - start_time) < micro_seconds)
        ;
}

void game(int w, int h) {
    unsigned univ[h][w];
    char *filename = "data.txt";
    FILE *fp = fopen(filename, "r");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int ch = 0;
            ch = fgetc(fp);
            univ[i][j] = ch - '0';
        }
    }
    fclose(fp);

    int count = 0, speed = 500;
    while (count < 1000) {
        printf("\033[27;3H\033\b\033\b\033\b");
        draw(univ, w, h);
        evolve(univ, w, h);
        char ch = 'w';
        if (ch == 'w') {
            if (speed > 50) {
                speed = speed - 50;
            }
        }
        if (ch == 's') {
            if (speed > 1500) {
                speed = speed + 50;
            }
        }
        printf("\033[27;0H%d", speed);
        delay(speed);
        count++;
    }
}
// дать возможность пользователю завершить программу досрочно
// кнопки ускорения замедления