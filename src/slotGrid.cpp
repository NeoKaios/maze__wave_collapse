#include "slotGrid.h"

slotGrid::slotGrid(int h, int v)
{
    Hgrid = h;
    Vgrid = v;
    for (int i = 0; i < Vgrid; ++i)
    {
        vector<SetOfPieces> row(Hgrid);
        possibilities.push_back(row);
    }
}

slotGrid::~slotGrid()
{
}

void slotGrid::draw(sdlHandle &win)
{
    for (int i = 0; i < Vgrid; ++i)
    {
        for (int j = 0; j < Hgrid; ++j)
        {
            drawSlot(win, i, j);
        }
    }
}

void slotGrid::drawSlot(sdlHandle &win, int x, int y)
{
    if (possibilities[x][y].isCollapsed())
    {
        possibilities[x][y].getFirst().draw(win, x, y);
    }
    else
    {
        possibilities[x][y].drawPossible(win, x, y);
    }
}