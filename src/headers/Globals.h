#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class Globals
{
    public:
    static Board* board;
    static bool f3On;
    static bool isWhitePlaying;
    static void Update();
    static void ToggleTurn();
};

#endif