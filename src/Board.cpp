#include "headers/Board.h"
#include "headers/ChessNotation.h"
#include "headers/Globals.h"
#include "headers/Piece.h"
#include "headers/raylib.h"
#include <cmath>
#include <string>

Board::Board(Vector2 size) : size(size) {}
Board::~Board() {}

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
                
                for(Piece* piece : Piece::pieces)
                {
                    if(clickedPos.x == piece->pos.x && clickedPos.y == piece->pos.y)
                    {
                        for (Vector2 avPosition : piece->availablePositions) 
                        {
                            if (x == avPosition.x && y == avPosition.y) 
                            {
                                color = BLUE; // Highlight available positions
                                break; 
                            }
                        }
                    }
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
                
                for(Piece* piece : Piece::pieces)
                {
                    if(clickedPos.x == piece->pos.x && clickedPos.y == piece->pos.y)
                    {
                        for (Vector2 avPosition : piece->availablePositions) 
                        {
                            if (x == avPosition.x && y == avPosition.y) 
                            {
                                color = DARKBLUE; // Highlight available positions
                                break; 
                            }
                        }
                    }
                }
            }
            DrawRectangle(x * tilesize, y * tilesize, tilesize, tilesize, color);
            if(Globals::f3On)
            {
                string chessPos = string(1, ChessNotation::VecToCharInt({(float)x, (float)y}).first) + to_string(ChessNotation::VecToCharInt({(float)x, (float)y}).second);
                DrawText(chessPos.c_str(), x * tilesize, y * tilesize, 10, BLACK); 
            }
        }
    }
    
    if(Globals::f3On)
    {
        string posString = "(" + to_string(static_cast<int>(clickedPos.x)) + ", " + to_string(static_cast<int>(clickedPos.y)) + ")";
        string posString2 = "(" + to_string(static_cast<int>(GetMousePosition().x)) + ", " + to_string(static_cast<int>(GetMousePosition().y)) + ")";
        DrawText(posString.c_str(), 10, 10, 20, BLACK);
        DrawText(posString2.c_str(), 10, 40, 20, BLACK);
    }
}