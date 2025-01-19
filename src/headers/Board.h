#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"
#include "vector"

class Board
{
    public:
    Vector2 size;
    const static int tilesize = 75;
    Vector2 selPos = {-1, -1};
    Vector2 movedPos = {-1, -1};
    Vector2 clickedPos = {-1, -1};
    Vector2 clickedMark = {-1, -1};
    Board(Vector2 size);
    ~Board();
    void Update();
    void Draw();
};

#endif
