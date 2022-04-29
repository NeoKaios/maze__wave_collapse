
#ifndef SETOFPIECES_H
#define SETOFPIECES_H

#include <unordered_set>
#include "piece.h"
#include <iostream>

using namespace std;

class SetOfPieces
{
    unordered_set<Piece, HashPiece> setPiece;

public:
    SetOfPieces();
    void add(Piece &);
    int remove(Piece &);

    Piece popRand();

    void addAll();
    void print();

    bool isCollapsed() const;
    void drawPossible(sdlHandle &, int, int) const;

    Piece getFirst() const;
};
#endif