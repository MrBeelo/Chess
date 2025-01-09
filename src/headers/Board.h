#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"
#include "vector"

class Board
{
    public:
    Vector2 size;
    const static int tilesize = 75;
    Vector2 clickedPos = {-1, -1};
    Vector2 clickedMark = {-1, -1};
    Board(Vector2 size);
    void Update();
    void Draw();
};

#endif
