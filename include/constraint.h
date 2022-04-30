#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <unordered_set>
#include "piece.h"
#include <iostream>

class Piece;
class HashPiece;

enum constraintType
{
    WallConstraint = 2,
    RoadConstraint = 3,
    Everything = 0
};

class Constraint
{
private:
    // constraintType left;
    // constraintType top;
    // constraintType right;
    // constraintType bot;

    // in order top, left, right, bot
    constraintType arr[4] = {Everything, Everything, Everything, Everything};

public:
    Constraint();
    int reduceConstraint(std::unordered_set<Piece, HashPiece> &);
    constraintType getConsOfDir(direction) const;
    static int compare(constraintType, constraintType);
    void print() const;
    static bool respectConstraint(Piece const &, direction, constraintType);
};

#endif