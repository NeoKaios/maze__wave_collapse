#include "constraint.h"
int Constraint::reduceConstraint(std::unordered_set<Piece, HashPiece> const &pieceSet)
{

    return 0;
}

constraintType Constraint::getConsOfDir(direction d) const
{
    switch (d)
    {
    case Top:
        return top;
    case Bot:
        return bot;
    case Right:
        return right;
    case Left:
        return left;
    }
    return Everything;
}

int Constraint::compare(constraintType cons1, constraintType cons2)
{
    int i = cons1 - cons2;
    if (i == -1 || i == 1) // Road against Wall or reverse
    {
        return -1;
    }
    else if (i < -1) // Everything against Road or Wall
    {
        return 1;
    }
    else // Equality, Road or Wall against Everything
    {
        return 0;
    }
}

bool Constraint::respectConstraint(Piece const &p, direction d, constraintType cons)
{
    return true;
}
