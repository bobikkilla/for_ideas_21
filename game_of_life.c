#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <time.h>

#define MAX_X 80
#define MAX_Y 25

void draw(void *u, int w, int h); // отрисовка
void evolve(void *u, int w, int h); // функция расчёта живых/мёртвых клеток
void delay(int milli_seconds); // простенькая функция задержки
void game(int w, int h); // функция игры
char getch(); // символы в режиме реального времени(за счёт режима терминала)

int main() {
  struct termios oldSettings, newSettings; // канон > неканон
  stdin = freopen("/dev/tty", "r", stdin);
  fcntl(0, F_SETFL, O_NONBLOCK);
  tcgetattr(0, &oldSettings);
  newSettings = oldSettings;
  newSettings.c_lflag &= ~ICANON;
  newSettings.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &newSettings);
  game(MAX_X, MAX_Y); // функция игры
  tcsetattr(0, TCSANOW, &oldSettings);
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
          if (univ[(y1 + h) % h][(x1 + w) % w])
            n++;
      if (univ[y][x])
        n--;
      new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
    }
  for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
      univ[y][x] = new[y][x];
}

void delay(int milli_seconds) {
  clock_t start_time = clock();
  clock_t end_time = milli_seconds * (CLOCKS_PER_SEC / 1000);
  while (clock() - start_time < end_time)
    ;
}

void game(int w, int h) {
  unsigned univ[h][w];
  char *filename = "data.txt";
  int speed = 500, speed_delta = 25;

  FILE *fp = fopen(filename, "r");
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int ch = 0;
      ch = fgetc(fp); // считывание из файла по 1 символу
      univ[i][j] = ch - '0';
    }
  }
  fclose(fp);
  while (1) {
    draw(univ, w, h);
    delay(speed);
    evolve(univ, w, h);
    char ch = getch(0);
    switch (ch) {
    case 'w':
      if (speed > 50) {
        speed = speed - speed_delta;
      }
      break;
    case 's':
      if (speed < 1500) {
        speed = speed + speed_delta;
      }
      break;
    default:
    }
    if (ch == 'q') {
      break;
    }
    printf("\033[29;4Hw to speed up, s to slow down, q to quit");
  }
}

char getch() {
  char ch;
  ch = getchar();
  return ch;
}

// дать возможность пользователю завершить программу досрочно
// кнопки ускорения замедления
