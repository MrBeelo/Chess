#include "headers/Sounds.h"

Sound Sounds::moveSelf;
Sound Sounds::moveOpponent;

void Sounds::LoadContent()
{
    moveSelf = LoadSound("sounds/move-self.wav");
    moveOpponent = LoadSound("sounds/move-opponent");
    SetSoundVolume(moveSelf, 1.0f);
    SetSoundVolume(moveOpponent, 1.0f);
}

void Sounds::UnloadContent()
{
    UnloadSound(moveSelf);
    UnloadSound(moveOpponent);
}