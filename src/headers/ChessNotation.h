#ifndef CHESSNOTATION_H
#define CHESSNOTATION_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class ChessNotation
{
    public:
    static pair<char, int> VecToCharInt(Vector2 vector2);
    static Vector2 CharIntToVec(char file, int rank);
};

#endif