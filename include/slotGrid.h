#ifndef SLOTGRID_H
#define SLOTGRID_H

#include "setofpieces.h"
#include <vector>
#include <iostream>

using namespace std;

class slotGrid
{
    int Hgrid, Vgrid;

    vector<vector<SetOfPieces>> possibilities;

public:
    slotGrid(int h, int v);

    ~slotGrid();
    void draw(sdlHandle &);

private:
    void drawSlot(sdlHandle &, int, int);
};
#endif