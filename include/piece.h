#ifndef PIECE_H
#define PIECE_H

#include "sdlHandle.h"
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <string>

#define NB_PIECE 17

enum direction
{
    Top = 1,
    Right = 5,
    Left = 3,
    Bot = 7
};

enum pieceIdx
{
    Crossroad = 0,
    Deadend_B,
    Deadend_L,
    Deadend_T,
    Deadend_R,
    Angle_BL,
    Angle_TL,
    Angle_TR,
    Angle_BR,
    Line_H,
    Line_V,
    Tetris_B,
    Tetris_L,
    Tetris_T,
    Tetris_R,
    Wall,
    Room
};

class Piece
{
private:
    static char pieces[NB_PIECE][10];
    pieceIdx type;

public:
    Piece();
    Piece(pieceIdx _type);

    void draw(sdlHandle &window, int x, int y);

    void setType(pieceIdx typeIdx)
    {
        type = typeIdx;
    }
    pieceIdx getType() const
    {
        return type;
    }
    std::string ToString() const;
    bool operator==(Piece const &) const;
    int constraintOnDIr(direction) const;
    char *getPieceDef() const;

    static int def(char c);
};

// class for hash function
class HashPiece
{
public:
    size_t operator()(const Piece &p) const
    {
        return (int)p.getType();
    }
};

#endif