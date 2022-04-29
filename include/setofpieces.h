
#ifndef SETOFPIECES_H
#define SETOFPIECES_H

#include <iostream>
// #include "piece.h"
#include "constraint.h"

using namespace std;

class SetOfPieces
{
private:
    unordered_set<Piece, HashPiece> pieceSet;
    bool collapsed;
    Piece collapsedPiece;
    Constraint constraint;

public:
    SetOfPieces();

    Piece popRand();

    void addAll();
    void print();
    void collapseSlot();
    bool isCollapsed();
    void drawPossible(sdlHandle &, int, int) const;

    int applyConstraints(direction, constraintType);

    Piece getFirst() const;

private:
    void add(Piece &);
    int remove(Piece &);
};
#endif