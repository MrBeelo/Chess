#include "headers/Globals.h"

bool Globals::f3On = false;

void Globals::Update()
{
    if(IsKeyPressed(KEY_F3))
		{
		    if(Globals::f3On)
			{
			    Globals::f3On = false;
			} else {
			    Globals::f3On = true;
			}
		}
}