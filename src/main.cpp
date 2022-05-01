#include "slotGrid.h"
#include <iostream>

void temp()
{
    srand(time(NULL));
    int gridSize = 10;
    SlotGrid *grids = new SlotGrid(gridSize, gridSize);

    grids->solve();
    /*    SetOfPieces *s = new SetOfPieces();

        s->addAll();
        s->print();
        Piece p = s->popRand();
        s->popRand();
        s->popRand();
        s->popRand();
        s->popRand();
        cout << p.ToString() << endl;
        s->print();*/
}

int main()
{
    srand(time(NULL));
    int gridSize = 15;
    sdlHandle *win = new sdlHandle(3 * gridSize, 3 * gridSize, 150 / gridSize);
    win->init();
    win->clear();
    SlotGrid *grids = new SlotGrid(gridSize, gridSize);
    grids->solve();
    grids->draw(*win);
    win->updateScreen();

    while (1 - grids->solveDraw(*win, .05))
    {
        delete (grids);
        grids = new SlotGrid(gridSize, gridSize);
        sleep(5);
    }
    cout << "here\n";
    delete (grids);
    // win->waitAndClose(50);
    delete (win);
    return 0;

    /*
    int idx = 0;
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            Piece *piece = new Piece(pieceIdx(idx));
            piece->draw(*win, i, j);
            delete (piece);

            if (idx < NB_PIECE - 1)
            {
                idx++;
            }
        }
    }
    win->updateScreen();
    */
    // sleep(1);
    // return 0;
}