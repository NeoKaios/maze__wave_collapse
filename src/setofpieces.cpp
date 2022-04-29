#include "setofpieces.h"

using namespace std;

SetOfPieces::SetOfPieces(){

};

void SetOfPieces::add(Piece &toAdd)
{
    pieceSet.emplace(toAdd);
};
int SetOfPieces::remove(Piece &toRemove)
{
    return pieceSet.erase(toRemove);
};

Piece SetOfPieces::popRand()
{
    int pos = rand() % pieceSet.size();
    unordered_set<Piece>::iterator itr = pieceSet.begin();
    for (int i = 0; i < pos; i++)
    {
        itr++;
    }
    return pieceSet.extract(itr).value();
};

void SetOfPieces::addAll()
{
    for (int j = 0; j < NB_PIECE; ++j)
    {
        Piece p = Piece(pieceIdx(j));
        add(p);
    }
    collapsed = false;
};

void SetOfPieces::print()
{
    unordered_set<Piece>::iterator itr;
    for (itr = pieceSet.begin(); itr != pieceSet.end(); itr++)
    {
        cout << (*itr).ToString() << " ";
    }
    cout << endl;
};

bool SetOfPieces::isCollapsed()
{
    collapsed = (pieceSet.size() == 1);
    return collapsed;
}

Piece SetOfPieces::getFirst() const
{
    return *pieceSet.begin();
}

void SetOfPieces::drawPossible(sdlHandle &win, int x, int y) const
{
}

void SetOfPieces::collapseSlot()
{
    collapsedPiece = popRand(); // Here take a random piece, but it should evolve into a heuristic
    pieceSet.clear();
    collapsed = true;
}

int SetOfPieces::applyConstraints(direction d, constraintType cons)
{
    // Remove some Piece due to the constraint
    // If collapsed, nothing can change
    if (collapsed)
    {
        return 0;
    }

    unordered_set<Piece>::iterator itr;
    // Check if this set is more constrained than the constraint to apply
    switch (Constraint::compare(constraint.getConsOfDir(d), cons))
    {
    case -1: // Incompatibility : impossible to finish
        return -1;
    case 0: // This set is already more constrained
        return 0;
    case 1: // This set is less constrained, need to apply new constraint
    {
        // remove all that do not fit the d//cons constraint
        bool hasChanged = false;
        unordered_set<Piece>::iterator itr;
        for (itr = pieceSet.begin(); itr != pieceSet.end(); itr++)
        {
            if (!Constraint::respectConstraint(*itr, d, cons))
            {
                pieceSet.extract(itr);
                hasChanged = true;
            }
        }
        if (isCollapsed())
        {
            collapsedPiece = getFirst();
            return constraint.reduceConstraint(pieceSet);
        }
        else
        {
            return hasChanged ? constraint.reduceConstraint(pieceSet) : 0;
        }
        // Reduce the constraint to the new set of pieces
    }
    default:
        return -1;
    }
}