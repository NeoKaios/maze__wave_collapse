
#ifndef SETOFPIECES_H
#define SETOFPIECES_H

#include <iostream>
#include "constraint.h"
#include <vector>

using namespace std;

class SetOfPieces
{
public:
    unordered_set<Piece, HashPiece> pieceSet;
    bool collapsed;
    Piece collapsedPiece;
    Constraint constraint;

public:
    SetOfPieces();

    Piece popRand();

    void addAll();
    void print();
    void printCons();
    void collapseSlot();
    bool isCollapsed();
    void draw(sdlHandle &, int, int);

    int applyConstraints(direction, constraintType);

    Piece getFirst() const;

private:
    void add(Piece &);
    int remove(Piece const &);
    void drawPossible(sdlHandle &, int, int);
};
#endif