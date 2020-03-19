#include <raylib.h>
#include <stdio.h>
#include "ui.h"

#define SCREEN_WIDTH 1145
#define SCREEN_HEIGHT 795
#define GRID_SIZE 15
#define BORDER_SIZE 20
#define STATUS_BAR_SIZE 25

void InitBase()
{
    ClearBackground(RAYWHITE);

    DrawStatusBar();
    DrawGrids();
    DrawBorders();
    DrawScaleX();
    DrawScaleY();
}

void DrawStatusBar()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, STATUS_BAR_SIZE, BLACK);
    DrawLine(0, STATUS_BAR_SIZE, SCREEN_WIDTH, STATUS_BAR_SIZE, RAYWHITE);
}

void DrawGeneration(char *generationStr)
{
    DrawText("Generation:", 2, 2, 21, RAYWHITE);
    int nPixel = 2 + MeasureText("Generation:", 21);

    int m = MeasureText(generationStr, 21);
    int offSet = 120 - m;
    
    DrawText(generationStr, nPixel + offSet, 2, 21, RAYWHITE);
}

void DrawGrids()
{
    int x1, x2, y1, y2;
    x1 = BORDER_SIZE;
    x2 = SCREEN_WIDTH,
    y1 = y2 = STATUS_BAR_SIZE + BORDER_SIZE + GRID_SIZE;

    for (; y1 < SCREEN_HEIGHT; y1 += GRID_SIZE, y2 += GRID_SIZE)
    {
        DrawLine(x1, y1, x2, y2, BLACK);
    }

    x1 = x2 = BORDER_SIZE + GRID_SIZE;
    y1 = STATUS_BAR_SIZE + BORDER_SIZE;
    y2 = SCREEN_HEIGHT;

    for (; x1 < SCREEN_WIDTH; x1 += GRID_SIZE, x2 += GRID_SIZE)
    {
        DrawLine(x1, y1, x2, y2, BLACK);
    }
}

void DrawBorders()
{
    DrawRectangle(0, STATUS_BAR_SIZE, SCREEN_WIDTH, BORDER_SIZE, BLACK);
    DrawRectangle(0, STATUS_BAR_SIZE, BORDER_SIZE, SCREEN_HEIGHT, BLACK);
}

void DrawScaleX()
{
    int x = BORDER_SIZE, y = STATUS_BAR_SIZE + 5, size = 6, c = 1, xOffSet = 0;
    char s[3];

    while (x < SCREEN_WIDTH)
    {
        sprintf(s, "%d", c);

        xOffSet = (GRID_SIZE - MeasureText(s, size)) / 2;
        DrawText(s, x + xOffSet, y, size, RAYWHITE);
        x += GRID_SIZE;
        c++;
    }
}

void DrawScaleY()
{
    int y = STATUS_BAR_SIZE + BORDER_SIZE, size = 6, c = 1, xOffSet = 0;
    char s[3];

    while (y < SCREEN_HEIGHT)
    {
        sprintf(s, "%d", c);

        xOffSet = (GRID_SIZE - MeasureText(s, size)) / 2;
        DrawText(s, xOffSet, y + 3, size, RAYWHITE);
        y += GRID_SIZE;
        c++;
    }
}

void DrawMouseTrace()
{
    Vector2 v = GetMousePosition();
    int x = v.x <= SCREEN_WIDTH && v.x >= 0;
    int y =v.y <= SCREEN_HEIGHT && v.y >= STATUS_BAR_SIZE;
    if (x && y)
    {
        DrawLine(v.x, STATUS_BAR_SIZE, v.x, SCREEN_HEIGHT, RED);
        DrawLine(0, v.y, SCREEN_WIDTH, v.y, RED);
    }
}

Vector2 TransformToScreenPoint(int x, int y)
{
    int nX, nY;
    nX = nY = BORDER_SIZE;

    nX += GRID_SIZE * (x - 1);
    nY += GRID_SIZE * (y - 1);

    Vector2 v = {nX, nY};

    return v;
}

Vector2 TransformToGridPoint(int x, int y)
{
    int nX, nY;

    nX = ((x - BORDER_SIZE) / GRID_SIZE) + 1;
    nY = ((y - BORDER_SIZE) / GRID_SIZE) + 1;

    Vector2 v = {nX, nY};

    return v;
}