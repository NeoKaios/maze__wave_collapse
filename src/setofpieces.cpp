#include "setofpieces.h"

using namespace std;

SetOfPieces::SetOfPieces(){

};
void SetOfPieces::add(Piece &toAdd)
{
    setPiece.emplace(toAdd);
};
int SetOfPieces::remove(Piece &toRemove)
{
    setPiece.erase(toRemove);
    return 0;
};

Piece SetOfPieces::popRand()
{
    int pos = rand() % setPiece.size();
    unordered_set<Piece>::iterator itr = setPiece.begin();
    for (int i = 0; i < pos; i++)
    {
        itr++;
    }
    Piece p = (*itr);
    remove(p);
    return p;
};

void SetOfPieces::addAll()
{
    for (int j = 0; j < NB_PIECE; ++j)
    {
        Piece p = Piece(pieceIdx(j));
        add(p);
    }
};

void SetOfPieces::print()
{
    unordered_set<Piece>::iterator itr;
    for (itr = setPiece.begin(); itr != setPiece.end(); itr++)
    {
        cout << (*itr).ToString() << " ";
    }
    cout << endl;
};

bool SetOfPieces::isCollapsed() const
{
    return setPiece.size() == 1;
}

Piece SetOfPieces::getFirst() const
{
    return *setPiece.begin();
}
void SetOfPieces::drawPossible(sdlHandle &win, int x, int y) const
{
}