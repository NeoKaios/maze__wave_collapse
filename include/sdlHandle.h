#ifndef SDLHANDLE_H
#define SDLHANDLE_H

#include "SDL.h"
#include <unistd.h>

class sdlHandle
{

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int cell_size;
    int V_cells;
    int H_cells;

    // The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    // The window renderer
    SDL_Renderer *gRenderer = NULL;

public:
    sdlHandle(int Vcells, int Hcells, int cellSize);

    bool init();
    void close();

    void clear();
    void updateScreen();
    int waitAndClose(int);
    int checkForClose();
    void drawCellGreyScale(int x, int y, float color);
};
#endif