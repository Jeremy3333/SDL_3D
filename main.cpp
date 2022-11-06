// test sdl

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#include "RenderWindow.hpp"

void draw(RenderWindow &window)
{
    window.clear();
    // draw black background
    window.color(0, 0, 0, 255);
    window.drawBackground();
}

struct cube3D
{
    float point[8][3];
    int line[12][2];
};

cube3D init()
{
    cube3D cube;
    // init points of cube (x, y, z) with the origin at the center of the screen
    cube.point[0][0] = 500;
    cube.point[0][1] = 200;
    cube.point[0][2] = 400;
    cube.point[1][0] = 600;
    cube.point[1][1] = 200;
    cube.point[1][2] = 250;
    cube.point[2][0] = 450;
    cube.point[2][1] = 200;
    cube.point[2][2] = 150;
    cube.point[3][0] = 350;
    cube.point[3][1] = 200;
    cube.point[3][2] = 300;
    cube.point[4][0] = 500;
    cube.point[4][1] = 380;
    cube.point[4][2] = 400;
    cube.point[5][0] = 600;
    cube.point[5][1] = 380;
    cube.point[5][2] = 250;
    cube.point[6][0] = 450;
    cube.point[6][1] = 380;
    cube.point[6][2] = 150;
    cube.point[7][0] = 350;
    cube.point[7][1] = 380;
    cube.point[7][2] = 300;
    // init lines
    cube.line[0][0] = 0;
    cube.line[0][1] = 1;
    cube.line[1][0] = 1;
    cube.line[1][1] = 2;
    cube.line[2][0] = 2;
    cube.line[2][1] = 3;
    cube.line[3][0] = 3;
    cube.line[3][1] = 0;
    cube.line[4][0] = 0;
    cube.line[4][1] = 4;
    cube.line[5][0] = 1;
    cube.line[5][1] = 5;
    cube.line[6][0] = 2;
    cube.line[6][1] = 6;
    cube.line[7][0] = 3;
    cube.line[7][1] = 7;
    cube.line[8][0] = 4;
    cube.line[8][1] = 5;
    cube.line[9][0] = 5;
    cube.line[9][1] = 6;
    cube.line[10][0] = 6;
    cube.line[10][1] = 7;
    cube.line[11][0] = 7;
    cube.line[11][1] = 4;
    return cube;
}

void rotate(cube3D &cube, float angle, float center[3])
{
    float x, y, z;
    for (int i = 0; i < 8; i++)
    {
        x = cube.point[i][0] - center[0];
        y = cube.point[i][1] - center[1];
        z = cube.point[i][2] - center[2];
        cube.point[i][0] = x * cos(angle) - y * sin(angle) + center[0];
        cube.point[i][1] = x * sin(angle) + y * cos(angle) + center[1];
        cube.point[i][2] = z;
    }
}

void rotateX(cube3D &cube, float angle, float center[3])
{
    float y, z;
    for (int i = 0; i < 8; i++)
    {
        y = cube.point[i][1] - center[1];
        z = cube.point[i][2] - center[2];
        cube.point[i][1] = y * cos(angle) - z * sin(angle) + center[1];
        cube.point[i][2] = y * sin(angle) + z * cos(angle) + center[2];
    }
}

void rotateY(cube3D &cube, float angle, float center[3])
{
    float x, z;
    for (int i = 0; i < 8; i++)
    {
        x = cube.point[i][0] - center[0];
        z = cube.point[i][2] - center[2];
        cube.point[i][0] = x * cos(angle) - z * sin(angle) + center[0];
        cube.point[i][2] = x * sin(angle) + z * cos(angle) + center[2];
    }
}

void rotateZ(cube3D &cube, float angle, float center[3])
{
    float x, y;
    for (int i = 0; i < 8; i++)
    {
        x = cube.point[i][0] - center[0];
        y = cube.point[i][1] - center[1];
        cube.point[i][0] = x * cos(angle) - y * sin(angle) + center[0];
        cube.point[i][1] = x * sin(angle) + y * cos(angle) + center[1];
    }
}

void drawCube(RenderWindow &window, cube3D cube, int focalLength)
{
    int x[8], y[8];
    for (int i = 0; i < 8; i++)
    {
        x[i] = (focalLength * cube.point[i][0]) / (focalLength + cube.point[i][2]);
        y[i] = (focalLength * cube.point[i][1]) / (focalLength + cube.point[i][2]);
    }
    window.color(255, 255, 255, 255);
    for (int i = 0; i < 12; i++)
    {
        window.drawLine(x[cube.line[i][0]], y[cube.line[i][0]], x[cube.line[i][1]], y[cube.line[i][1]]);
    }
}

int main(int argc, char *argv[])
{
    RenderWindow window("test", 800, 600);
    SDL_Event event;
    bool quit = false;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    cube3D cube = init();
    int focalLength = 1000;
    float center[3] = {475, 290, 275};
    float centerY[2] = {475, 275};
    while (!quit)
    {
        // avoid the program to go too fast
        float startTicks = SDL_GetTicks();
        float timeStepMs = 2000.0f / window.getRefreshRate();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
            {
                quit = true;
            }
        }
        window.clear();

        // rotate(cube, 0.01, center);

        if (state[SDL_SCANCODE_D])
        {
            rotateY(cube, 0.01, center);
        }
        if (state[SDL_SCANCODE_A])
        {
            rotateY(cube, -0.01, center);
        }
        if (state[SDL_SCANCODE_W])
        {
            rotateX(cube, 0.01, center);
        }
        if (state[SDL_SCANCODE_S])
        {
            rotateX(cube, -0.01, center);
        }
        if (state[SDL_SCANCODE_Q])
        {
            rotateZ(cube, 0.01, center);
        }
        if (state[SDL_SCANCODE_E])
        {
            rotateZ(cube, -0.01, center);
        }

        draw(window);
        drawCube(window, cube, focalLength);

        window.display();

        // wait for the next frame
        float frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < timeStepMs)
            SDL_Delay(timeStepMs - frameTicks);
    }
    window.cleanUp();
    return 0;
}