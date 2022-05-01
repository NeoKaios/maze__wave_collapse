
#ifndef SETOFPIECES_H
#define SETOFPIECES_H

#include <iostream>
#include "constraint.h"
#include <vector>
#include <deque>

using namespace std;

class SetOfPieces
{
private:
    unordered_set<Piece, HashPiece> pieceSet;
    bool collapsed;
    Piece collapsedPiece;
    Constraint constraint;

public:
    int id;
    static int minUnusedId;

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
    constraintType getConsOnDir(direction) const;
    Piece getFirst() const;
    bool operator==(SetOfPieces const &) const;

private:
    void add(Piece &);
    int remove(Piece const &);
    void drawPossible(sdlHandle &, int, int);
};
#endif