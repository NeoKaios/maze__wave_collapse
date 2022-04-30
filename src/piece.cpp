#include "piece.h"

using namespace std;

char Piece::pieces[NB_PIECE][10] = {
    // Crossroad
    "101000101",
    // Dead end
    "111101101",
    "111001111",
    "101101111",
    "111100111",
    // Angle
    "111001101",
    "101001111",
    "101100111",
    "111100101",
    // Line
    "111000111", // H
    "101101101", // V
    // Tetris
    "111000101",
    "101001101",
    "101000111",
    "101100101",

    "111111111", // Wall
    "000000000"  // Room
};

const string piecesName[] = {
    "Crossroad",
    "Deadend_B",
    "Deadend_L",
    "Deadend_T",
    "Deadend_R",
    "Angle_BL",
    "Angle_TL",
    "Angle_TR",
    "Angle_BR",
    "Line_H",
    "Line_V",
    "Tetris_B",
    "Tetris_L",
    "Tetris_T",
    "Tetris_R",
    "Wall",
    "Room"};

Piece::Piece()
{
    type = pieceIdx(rand() % NB_PIECE);
    // type = Wall;
}

Piece::Piece(pieceIdx _type)
{
    if ((int)_type < 0 || (int)_type >= NB_PIECE)
    {
        type = Room;
    }
    else
    {
        type = _type;
    }
}

void Piece::draw(sdlHandle &window, int x, int y)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int color = (int)pieces[type][3 * i + j] - 48;
            window.drawCellGreyScale(x * 3 + i, y * 3 + j, color);
        }
    }
}

std::string Piece::ToString() const
{
    return piecesName[(int)type];
}

bool Piece::operator==(Piece const &toCompare) const
{
    return this->type == toCompare.type;
};

int Piece::constraintOnDIr(direction d) const
{
    return (int)(pieces[type][d]) - 48;
}
char *Piece::getPieceDef() const
{
    return pieces[type];
}