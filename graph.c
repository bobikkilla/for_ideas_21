#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT 25
#define WIDTH 80
#define PI 3.141592653589793238462643383279

void draw();

int main() {
    draw();

    return 0;
}
// D(y) = [-1, 1], h(y) = 2/25 , D(x) = [0,4PI], h = PI/20, [0,0] = [0, 13]

void draw() {
    float hy = 2.0 / HEIGHT; // Масштаб высоты
    char to_draw[HEIGHT][WIDTH];
    
    // Заполнение фона
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            to_draw[i][j] = '.';
        }
    }

    // Расчет и отрисовка графика
    for (int x = 0; x < WIDTH; x++) {
        double iter = (4 * PI / WIDTH) * x; // Итерация по X с масштабом
        
        // input -> calculations and back here

        double result = sin(cos(2*iter));

        // Проверка на асимптоту
        if (fabs(result) > 100) continue; // Пропуск точки с сильным отклонением

        int plotY = HEIGHT / 2 - (int)(result / hy); // Перевод в систему координат сетки с учетом масштаба
        
        // Убеждаемся, что координата Y падает в пределы сетки
        if (plotY >= 0 && plotY < HEIGHT) {
            to_draw[plotY][x] = '*';
        }
    }

    // Вывод на экран
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", to_draw[y][x]);
        }
        printf("\n");
    }
}
