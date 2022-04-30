#include "slotGrid.h"

SlotGrid::SlotGrid(int h, int v)
{
    Hgrid = h;
    Vgrid = v;
    for (int i = 0; i < Vgrid; ++i)
    {
        vector<SetOfPieces> row(Hgrid);
        possibilities.push_back(row);
    }
}

SlotGrid::~SlotGrid()
{
}

void SlotGrid::draw(sdlHandle &win)
{
    for (int i = 0; i < Vgrid; ++i)
    {
        for (int j = 0; j < Hgrid; ++j)
        {
            possibilities[i][j].draw(win, i, j);
        }
    }
}

void SlotGrid::solve()
{
    SetOfPieces &sop = possibilities[0][0];
    vector<SetOfPieces> queue;
    for (int i = 0; i < Vgrid; ++i)
    {
        for (int j = 0; j < Hgrid; ++j)
        {
            possibilities[i][j].collapseSlot();
        }
    }
}