#include "slotGrid.h"

SlotGrid::SlotGrid(int h, int v)
{
    Hgrid = h;
    Vgrid = v;
    for (int i = 0; i < Vgrid; ++i)
    {
        vector<SetOfPieces> row(Hgrid);
        possibilities.push_back(row);
    }
    for (int i = 0; i < Vgrid; ++i)
    {
        for (int j = 0; j < Hgrid; ++j)
        {
            uncollapsed.push_back(&possibilities[i][j]);
        }
    }
}

SlotGrid::~SlotGrid()
{
}

void SlotGrid::draw(sdlHandle &win)
{
    for (int i = 0; i < Vgrid; ++i)
    {
        for (int j = 0; j < Hgrid; ++j)
        {
            possibilities[i][j].draw(win, i, j);
        }
    }
}
/* Put edge condition on the grid
 */
void SlotGrid::initSolve()
{
    for (int i = 0; i < Vgrid; ++i)
    {
        if (i == Vgrid / 2)
            continue;
        possibilities[i][0].applyConstraints(Left, WallConstraint);
        possibilities[i][Hgrid - 1].applyConstraints(Right, WallConstraint);
    }
    for (int j = 0; j < Hgrid; ++j)
    {
        if (j == Hgrid / 2)
            continue;
        possibilities[0][j].applyConstraints(Top, WallConstraint);
        possibilities[Vgrid - 1][j].applyConstraints(Bot, WallConstraint);
    }
    possibilities[Vgrid / 2][0].applyConstraints(Left, RoadConstraint);
    possibilities[Vgrid / 2][Hgrid - 1].applyConstraints(Right, RoadConstraint);
    possibilities[0][Hgrid / 2].applyConstraints(Top, RoadConstraint);
    possibilities[Vgrid - 1][Hgrid / 2].applyConstraints(Bot, RoadConstraint);
}
/*
Collapse one slot and apply the recursive wave
*/
void SlotGrid::solveOneStep()
{
    // cout << "       Uncoll size : " << uncollapsed.size() << endl;
    // Starting point of the collapsed
    SetOfPieces *collapsedSoP = uncollapsed[rand() % uncollapsed.size()];

    collapsedSoP->collapseSlot();
    /* Propagate collapse
    0 If queue empty, end; else pop first
    1 Apply constraint in all 4 dirs
    2 If applyCons == 1, (if SoP not in queue, put in queue), goto 0
    3 Else, goto 0
    */
    deque<SetOfPieces *> sopQueue;
    sopQueue.push_back(collapsedSoP);
    while (!sopQueue.empty())
    // for (int tmp = 0; tmp < 5; ++tmp)
    {
        SetOfPieces *sop = sopQueue.front();
        sopQueue.pop_front();
        int i, j;
        getCoord(*sop, &i, &j);
        // sop->print();
        // sop->printCons();
        if (i < Vgrid - 1) // Bot
        {
            // cout << "   Constraining bot\n";
            SetOfPieces *sopInArray = &possibilities[i + 1][j];
            // sopInArray->print();
            // sopInArray->printCons();
            if (sopInArray->applyConstraints(Top, sop->getConsOnDir(Bot)) == 1) // if modification of constraint
            {
                bool isInQueue = false;
                for (int k = 0; k < sopQueue.size(); ++k) // check if sopInArray is in queue
                {
                    if (sopQueue[k] == sopInArray)
                    {
                        isInQueue = true;
                        break;
                    }
                }
                if (!isInQueue) // if not in queue, add it
                {
                    sopQueue.push_back(sopInArray);
                }
            }
        }

        if (i > 0) // Top
        {
            // cout << "constraining top\n";
            SetOfPieces *sopInArray = &possibilities[i - 1][j];
            if (sopInArray->applyConstraints(Bot, sop->getConsOnDir(Top)) == 1) // if modification of constraint
            {
                bool isInQueue = false;
                for (int k = 0; k < sopQueue.size(); ++k) // check if sopInArray is in queue
                {
                    if (sopQueue[k] == sopInArray)
                    {
                        isInQueue = true;
                        break;
                    }
                }
                if (!isInQueue) // if not in queue, add it
                {
                    sopQueue.push_back(sopInArray);
                }
            }
        }
        if (j < Hgrid - 1) // Right
        {
            // cout << "constraining right\n";
            SetOfPieces *sopInArray = &possibilities[i][j + 1];
            if (sopInArray->applyConstraints(Left, sop->getConsOnDir(Right)) == 1) // if modification of constraint
            {
                bool isInQueue = false;
                for (int k = 0; k < sopQueue.size(); ++k) // check if sopInArray is in queue
                {
                    if (sopQueue[k] == sopInArray)
                    {
                        isInQueue = true;
                        break;
                    }
                }
                if (!isInQueue) // if not in queue, add it
                {
                    sopQueue.push_back(sopInArray);
                }
            }
        }
        if (j > 0) // Left
        {
            // cout << "constraining left\n";
            SetOfPieces *sopInArray = &possibilities[i][j - 1];
            if (sopInArray->applyConstraints(Right, sop->getConsOnDir(Left)) == 1) // if modification of constraint
            {
                bool isInQueue = false;
                for (int k = 0; k < sopQueue.size(); ++k) // check if sopInArray is in queue
                {
                    if (sopQueue[k] == sopInArray)
                    {
                        isInQueue = true;
                        break;
                    }
                }
                if (!isInQueue) // if not in queue, add it
                {
                    sopQueue.push_back(sopInArray);
                }
            }
        }
    }

    // Reduce the uncollapse vector
    for (int i = uncollapsed.size() - 1; i >= 0; i--)
        if (uncollapsed[i]->isCollapsed())
            uncollapsed.erase(uncollapsed.begin() + i);
}

/* Apply the full Wave Function Collapse Algorithm
 */
void SlotGrid::solve()
{
    initSolve();
    while (uncollapsed.size() != 0)
    // for (int temp = 0; temp < 40; ++temp)
    {
        solveOneStep();
    }
}

/* Solve WFC and draw each frame at [delay] interval.
Return 0 if solve complete, 1 if the window has closed during solve*/
int SlotGrid::solveDraw(sdlHandle &win, float delay)
{
    initSolve();
    while (uncollapsed.size() != 0)
    // for (int temp = 0; temp < 40; ++temp)
    {
        if (win.checkForClose())
        {
            cout << "Window closed during the solveDraw\n";
            return 1;
        }
        win.clear();
        draw(win);
        win.updateScreen();
        usleep(1000000 * delay);
        solveOneStep();
    }
    win.clear();
    draw(win);
    win.updateScreen();
    usleep(1000000 * delay);
    return 0;
}

void SlotGrid::getCoord(SetOfPieces const &sop, int *ip, int *jp) const
{
    bool notFound = false;
    int i = 0;
    int j = 0;
    for (int i = 0; i < Vgrid; ++i)
    {
        for (int j = 0; j < Hgrid; ++j)
            if (possibilities[i][j] == sop)
            {
                *ip = i;
                *jp = j;
                return;
            }
    }
    *ip = 0;
    *jp = 0;
    fprintf(stderr, "SetOfPieces coord not found !");
    return;
}