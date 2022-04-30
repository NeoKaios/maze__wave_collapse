#include "setofpieces.h"

using namespace std;

SetOfPieces::SetOfPieces()
{
    collapsed = false;
    addAll();
    constraint = Constraint();
};

void SetOfPieces::add(Piece &toAdd)
{
    pieceSet.emplace(toAdd);
};
int SetOfPieces::remove(Piece const &toRemove)
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

void SetOfPieces::printCons()
{
    constraint.print();
}

bool SetOfPieces::isCollapsed()
{
    collapsed = (pieceSet.size() == 1);
    return collapsed;
}

Piece SetOfPieces::getFirst() const
{
    return *pieceSet.begin();
}

void SetOfPieces::drawPossible(sdlHandle &win, int x, int y)
{
    float color[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int max = pieceSet.size();
    unordered_set<Piece>::iterator itr;
    for (itr = pieceSet.begin(); itr != pieceSet.end(); itr++)
    {
        string ps = itr->getPieceDef();
        for (int i = 0; i < 9; ++i)
        {
            color[i] += (int)(ps[i]) - 48;
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        color[i] /= (float)max;
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            win.drawCellGreyScale(x * 3 + i, y * 3 + j, color[3 * i + j]);
        }
    }
}

void SetOfPieces::draw(sdlHandle &win, int x, int y)
{
    if (collapsed)
    {
        collapsedPiece.draw(win, x, y);
    }
    else
    {
        drawPossible(win, x, y);
    }
}

void SetOfPieces::collapseSlot()
{
    collapsedPiece = popRand(); // Here take a random piece, but it should evolve into a heuristic
    pieceSet.clear();
    add(collapsedPiece);
    constraint.reduceConstraint(pieceSet);
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
        cout << "Incompatibility of constraints\n";
        return -1;
    case 0: // This set is already more constrained
        cout << "Already more constrained\n";
        return 0;
    case 1: // This set is less constrained, need to apply new constraint
    {
        // remove all that do not fit the d//cons constraint
        bool hasChanged = false;
        vector<Piece const *> toRemove;
        unordered_set<Piece>::iterator itr;
        for (itr = pieceSet.begin(); itr != pieceSet.end(); itr++)
        {
            if (!Constraint::respectConstraint(*itr, d, cons))
            {
                toRemove.push_back(&(*itr));
                hasChanged = true;
            }
        }
        for (Piece const *p : toRemove)
        {
            remove(*p);
        }
        if (isCollapsed())
        {
            cout << "Constraint have collapsed a set\n";
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