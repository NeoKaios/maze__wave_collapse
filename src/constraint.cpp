#include "constraint.h"

using namespace std;

const string consToString[] = {
    "Everything",
    "",
    "WallCons",
    "RoadCons"};

Constraint::Constraint()
{
}
void Constraint::print() const
{
    for (int i = 0; i < 4; ++i)
    {
        cout << consToString[arr[i]] << "  " << endl;
    }
}
int Constraint::reduceConstraint(std::unordered_set<Piece, HashPiece> &pieceSet)
{
    int max = pieceSet.size();
    bool hasChanged = false;
    int cnt[] = {0, 0, 0, 0};
    unordered_set<Piece>::iterator itr;
    for (itr = pieceSet.begin(); itr != pieceSet.end(); itr++)
    {
        cnt[0] += itr->constraintOnDIr(Top);
        cnt[1] += itr->constraintOnDIr(Left);
        cnt[2] += itr->constraintOnDIr(Right);
        cnt[3] += itr->constraintOnDIr(Bot);
    }

    for (int i = 0; i < 4; ++i)
    {
        if (cnt[i] == 0 || cnt[i] == max) // all road or all wall
        {
            if (arr[i] == Everything)
            {
                hasChanged = true;
                arr[i] = cnt[i] == 0 ? RoadConstraint : WallConstraint;
            }
        }
        else // some of both
        {
            if (arr[i] != Everything)
            {
                printf("strange stuff\n");
                return -1;
            }
        }
    }
    return hasChanged ? 1 : 0;
}

constraintType Constraint::getConsOfDir(direction d) const
{
    return arr[d / 2];
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
    if (cons == Everything)
    {
        return true;
    }
    else
    {
        // (3-cons) output 0 for roadCons and 1 for wallCons which is the same convention as pieces array
        return p.constraintOnDIr(d) == (3 - cons);
    }
}