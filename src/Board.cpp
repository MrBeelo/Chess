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
            for(Piece* piece : Piece::pieces)
            {
                if(piece->pos.x == clickedPos.x && piece->pos.y == clickedPos.y)
                {
                    selPos = piece->pos;
                    movedPos = {-1, -1};
                }
            }
        } else {
            clickedPos = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
            if(prevClickPos.x == clickedPos.x && prevClickPos.y == clickedPos.y)
            {
                clickedPos = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
                clickedPos = {-1, -1};
                clickedMark = {-1, -1};
                selPos = {-1, -1};
                movedPos = {-1, -1};
            } else {
                for(Piece* piece : Piece::pieces)
                {
                    if(piece->pos.x == prevClickPos.x && piece->pos.y == prevClickPos.y)
                    {
                        clickedPos = {floor(mouse.x / tilesize), floor(mouse.y / tilesize)};
                        Piece::MoveTo(piece, clickedPos, piece->id);
                        movedPos = clickedPos;
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
    Color lightSquare = {235, 236, 208, 255};
    Color darkSquare = {115, 149, 82, 255};
    Color selLight = {247, 247, 105, 255};
    Color selDark = {187, 203, 43, 255};
    Color markLight = {236, 126, 106, 255};
    Color markDark = {212, 108, 81, 255};
    for(int x = 0; x < size.x; x++)
    {
        for(int y = 0; y < size.y; y++)
        {
            Color color;
            if(x % 2 == y % 2) {
                if(clickedMark.x == x && clickedMark.y == y)
                {
                    color = markLight;
                } else {
                    color = lightSquare;
                }
                
                if((selPos.x == x && selPos.y == y) || (movedPos.x == x && movedPos.y == y))
                {
                    color = selLight;
                }
                
                for(Piece* piece : Piece::pieces)
                {
                    if(clickedPos.x == piece->pos.x && clickedPos.y == piece->pos.y)
                    {
                        //color = selLight;
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
                if(clickedMark.x == x && clickedMark.y == y)
                {
                    color = markDark;
                } else {
                    color = darkSquare;
                }
                
                if((selPos.x == x && selPos.y == y) || (movedPos.x == x && movedPos.y == y))
                {
                    color = selDark;
                }
                
                for(Piece* piece : Piece::pieces)
                {
                    if(clickedPos.x == piece->pos.x && clickedPos.y == piece->pos.y)
                    {
                        //color = selDark;
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
        string posString3 = "(" + to_string(static_cast<int>(selPos.x)) + ", " + to_string(static_cast<int>(selPos.y)) + ")";
        string posString4 = "(" + to_string(static_cast<int>(movedPos.x)) + ", " + to_string(static_cast<int>(movedPos.y)) + ")";
        DrawText(posString.c_str(), 10, 10, 20, BLACK);
        DrawText(posString2.c_str(), 10, 40, 20, BLACK);
        DrawText(posString3.c_str(), 10, 70, 20, BLACK);
        DrawText(posString4.c_str(), 10, 100, 20, BLACK);
    }
}