#include "headers/Board.h"
#include "headers/Globals.h"
#include "headers/InputManager.h"
#include <cmath>


bool InputManager::IsFirstClick(const Vector2& prevClickPos)
{
    return prevClickPos.x == -1 && prevClickPos.y == -1;
}

bool InputManager::IsSameClick(const Vector2& prevClickPos, const Vector2& clickedPos)
{
    return prevClickPos.x == clickedPos.x && prevClickPos.y == clickedPos.y;
}

void InputManager::HandleLeftClick(const Vector2& mouse, Vector2& clickedPos)
{
    Vector2 prevClickPos = clickedPos;
    clickedPos = {floor(mouse.x / Board::tilesize), floor(mouse.y / Board::tilesize)};

    if (IsFirstClick(prevClickPos))
    {
        Globals::board->SelectPiece();
    }
    else
    {
        if (IsSameClick(prevClickPos, clickedPos))
        {
            Globals::board->DeselectAll();
        }
        else
        {
            for(Piece* piece : Piece::pieces)
            {
                if(piece->pos.x == clickedPos.x && piece->pos.y == clickedPos.y)
                {
                    Globals::board->SelectPiece();
                }
            }
            Globals::board->MovePiece(prevClickPos);
        }
    }

    Globals::board->ValidateSelection();
}

void InputManager::HandleRightClick(const Vector2& mouse, Vector2& clickedMark)
{
    Vector2 prevClickMark = clickedMark;
    clickedMark = {floor(mouse.x / Board::tilesize), floor(mouse.y / Board::tilesize)};
    if (IsSameClick(prevClickMark, clickedMark))
    {
        clickedMark = {-1, -1};
    }
}