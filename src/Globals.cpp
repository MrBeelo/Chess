#include "headers/Globals.h"

Board* Globals::board = new Board({8, 8});
bool Globals::f3On = false;
bool Globals::isWhitePlaying = true;

void Globals::Update()
{
    if(IsKeyPressed(KEY_F3))
	{
	    Globals::f3On = !Globals::f3On;
	}
}

void Globals::ToggleTurn()
{
    Globals::isWhitePlaying = !Globals::isWhitePlaying;
}