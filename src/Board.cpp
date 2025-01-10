#include "headers/Board.h"
#include "headers/Piece.h"
#include <cmath>
#include <ostream>
#include <sstream>
#include <string>

Board::Board(Vector2 size) : size(size) {}
void Board::Update()
{
    Vector2 mouse = GetMousePosition();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 prevClickPos = clickedPos;
        if(prevClickPos.x == -1 && prevClickPos.y == -1)
        {
            clickedPos = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
        } else {
            clickedPos = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
            if(prevClickPos.x == clickedPos.x && prevClickPos.y == clickedPos.y)
            {
                clickedPos = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
                clickedPos = {-1, -1};
                clickedMark = {-1, -1};
            } else {
                for(Piece* piece : Piece::pieces)
                {
                    if(piece->pos.x == prevClickPos.x && piece->pos.y == prevClickPos.y)
                    {
                        clickedPos = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
                        Piece::MoveTo(piece, clickedPos, piece->id);
                        clickedPos = {-1, -1};
                    }
                }
            }
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        Vector2 prevClickMark = clickedMark;
        clickedMark = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
        if(prevClickMark.x == clickedMark.x && prevClickMark.y == clickedMark.y)
        {
            clickedMark = {-1, -1};
        }
    }
}

void Board::Draw()
{
    for(int x = 0; x < size.x; x++)
    {
        for(int y = 0; y < size.y; y++)
        {
            Color color;
            if(x % 2 == y % 2) {
                if(clickedPos.x == x && clickedPos.y == y)
                {
                    color = BLUE;
                } else if(clickedMark.x == x && clickedMark.y == y)
                {
                    color = RED;
                } else {
                    color = WHITE;
                }
            } else {
                if(clickedPos.x == x && clickedPos.y == y)
                {
                    color = DARKBLUE;
                } else if(clickedMark.x == x && clickedMark.y == y)
                {
                    color = MAROON;
                } else {
                    color = GREEN;
                }
            }
            DrawRectangle(x * tilesize, y * tilesize, tilesize, tilesize, color);
        }
    }
    
    ostringstream oss;
    ostringstream oss2;
    oss << "(" << clickedPos.x << ", " << clickedPos.y << ")";
    oss2 << "(" << GetMousePosition().x << ", " << GetMousePosition().y << ")";
    string posString = oss.str();
    string posString2 = oss2.str();
    DrawText(posString.c_str(), 10, 10, 20, BLACK);
    DrawText(posString2.c_str(), 10, 40, 20, BLACK);
}