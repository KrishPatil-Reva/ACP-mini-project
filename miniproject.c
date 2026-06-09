#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

// Initialize canvas
void initCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

// Display canvas
void displayCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

// Draw point safely
void drawPoint(int x, int y) {
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS) {
        canvas[x][y] = '*';
    }
}

// Draw line (simple)
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
        drawPoint(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

// Draw rectangle
void drawRectangle(int x, int y, int w, int h) {
    for (int i = 0; i < w; i++) {
        drawPoint(x, y + i);
        drawPoint(x + h - 1, y + i);
    }
    for (int i = 0; i < h; i++) {
        drawPoint(x + i, y);
        drawPoint(x + i, y + w - 1);
    }
}

// Draw triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

// Draw circle (midpoint idea)
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y) {
        drawPoint(xc + x, yc + y);
        drawPoint(xc - x, yc + y);
        drawPoint(xc + x, yc - y);
        drawPoint(xc - x, yc - y);
        drawPoint(xc + y, yc + x);
        drawPoint(xc - y, yc + x);
        drawPoint(xc + y, yc - x);
        drawPoint(xc - y, yc - x);

        x++;
        if (p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

// Clear canvas (delete all)
void clearCanvas() {
    initCanvas();
}

// Menu
void menu() {
    printf("\n--- 2D Graphics Editor ---\n");
    printf("1. Draw Line\n");
    printf("2. Draw Rectangle\n");
    printf("3. Draw Triangle\n");
    printf("4. Draw Circle\n");
    printf("5. Display Canvas\n");
    printf("6. Clear Canvas (Delete All)\n");
    printf("7. Exit\n");
    printf("Enter choice: ");
}

int main() {
    int choice;
    initCanvas();

    while (1) {
        menu();
        scanf("%d", &choice);

        if (choice == 1) {
            int x1, y1, x2, y2;
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            drawLine(x1, y1, x2, y2);
        }
        else if (choice == 2) {
            int x, y, w, h;
            printf("Enter top-left (x y), width and height: ");
            scanf("%d %d %d %d", &x, &y, &w, &h);
            drawRectangle(x, y, w, h);
        }
        else if (choice == 3) {
            int x1, y1, x2, y2, x3, y3;
            printf("Enter 3 points: ");
            scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
            drawTriangle(x1, y1, x2, y2, x3, y3);
        }
        else if (choice == 4) {
            int xc, yc, r;
            printf("Enter center (x y) and radius: ");
            scanf("%d %d %d", &xc, &yc, &r);
            drawCircle(xc, yc, r);
        }
        else if (choice == 5) {
            displayCanvas();
        }
        else if (choice == 6) {
            clearCanvas();
            printf("Canvas cleared!\n");
        }
        else if (choice == 7) {
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
