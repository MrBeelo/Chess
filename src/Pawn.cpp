#include "headers/Pawn.h"

Texture2D Pawn::textureWhite;
Texture2D Pawn::textureBlack;
vector<Pawn*> Pawn::pawns;

Pawn::Pawn(Vector2 pos, bool isWhite, int id) : Piece(pos, isWhite, id) {}

void Pawn::LoadContent()
{
    textureWhite = LoadTexture("sprites/wp.png");
    textureBlack = LoadTexture("sprites/bp.png");
}

void Pawn::UnloadContent()
{
    UnloadTexture(textureWhite);
    UnloadTexture(textureBlack);
}

void Pawn::Make(Vector2 pos, bool isWhite, int id)
{
    Pawn* pawn = new Pawn(pos, isWhite, id);
    pawns.push_back(pawn);
    pieces.push_back(pawn);
}

void Pawn::Make(char file, int rank, bool isWhite, int id)
{
    float x = file - 'A';
    float y = 7 - (rank - 1);
    Vector2 pos = {x, y};
    
    Make(pos, isWhite, id);
}

void Pawn::Update()
{ Piece::Update(); }

void Pawn::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}