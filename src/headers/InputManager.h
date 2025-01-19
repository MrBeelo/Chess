#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class InputManager
{
    public:
    static void HandleLeftClick(const Vector2& mouse, Vector2& clickedPos);
    static void HandleRightClick(const Vector2& mouse, Vector2& clickedMark);
    static bool IsFirstClick(const Vector2& prevClickPos);
    static bool IsSameClick(const Vector2& prevClickPos, const Vector2& clickedPos);
};

#endif