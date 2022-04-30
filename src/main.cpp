#include "slotGrid.h"
#include <iostream>
#include <unistd.h>

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
    int gridSize = 10;
    sdlHandle *win = new sdlHandle(3 * gridSize, 3 * gridSize, 150 / gridSize);
    SlotGrid *grids = new SlotGrid(gridSize, gridSize);
    win->init();
    win->clear();
    int idx = 0;
    grids->solve();
    grids->draw(*win);
    win->updateScreen();
    win->clear();
    /*
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
    return win->waitForClose(5);
    // sleep(1);
    // return 0;
}