#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <unordered_set>
#include "piece.h"

class Piece;
class HashPiece;

enum constraintType
{
    WallConstraint = 2,
    RoadConstraint = 3,
    Everything = 0
};

enum direction
{
    Top,
    Right,
    Left,
    Bot
};

class Constraint
{
private:
    constraintType left;
    constraintType top;
    constraintType right;
    constraintType bot;

public:
    int reduceConstraint(std::unordered_set<Piece, HashPiece> const &);
    constraintType getConsOfDir(direction) const;
    static int compare(constraintType, constraintType);
    static bool respectConstraint(Piece const &, direction, constraintType);
};

#endif