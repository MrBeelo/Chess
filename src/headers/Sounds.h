#ifndef SOUNDS_H
#define SOUNDS_H

#include "raylib.h"
#include "vector"

class Sounds
{
    public:
    static Sound moveSelf;
    static Sound moveOpponent;
    
    static void LoadContent();
    static void UnloadContent();
};

#endif