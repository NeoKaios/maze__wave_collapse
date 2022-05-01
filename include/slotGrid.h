#ifndef SLOTGRID_H
#define SLOTGRID_H

#include "setofpieces.h"
#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

class SlotGrid
{
    int Hgrid, Vgrid;

    vector<vector<SetOfPieces>> possibilities;
    vector<SetOfPieces *> uncollapsed; // Contain pointer to all uncollapsed SoP

public:
    SlotGrid(int h, int v);

    ~SlotGrid();
    void draw(sdlHandle &);
    void solve();
    int solveDraw(sdlHandle &, float);
    void solveOneStep();
    void initSolve();

private:
    void getCoord(SetOfPieces const &, int *, int *) const;
};
#endif