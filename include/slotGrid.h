#ifndef SLOTGRID_H
#define SLOTGRID_H

#include "setofpieces.h"
#include <vector>
#include <iostream>

using namespace std;

class SlotGrid
{
    int Hgrid, Vgrid;

    vector<vector<SetOfPieces>> possibilities;

public:
    SlotGrid(int h, int v);

    ~SlotGrid();
    void draw(sdlHandle &);
    void solve();
};
#endif