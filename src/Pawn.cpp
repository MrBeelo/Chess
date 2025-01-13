#include "headers/Pawn.h"
#include "headers/ChessNotation.h"

Texture2D Pawn::textureWhite;
Texture2D Pawn::textureBlack;
vector<Pawn*> Pawn::pawns;

Pawn::Pawn(Vector2 pos, bool isWhite, int id) : Piece(pos, isWhite, id) {}
Pawn::~Pawn() {}

void Pawn::LoadContent()
{
    textureWhite = LoadTexture("sprites/wp.png");
    textureBlack = LoadTexture("sprites/bp.png");
}

void Pawn::UnloadContent()
{
    UnloadTexture(textureWhite);
    UnloadTexture(textureBlack);
    for(Pawn* pawn : pawns)
    {
        delete pawn;
    }
}

void Pawn::Make(Vector2 pos, bool isWhite, int id)
{
    Pawn* pawn = new Pawn(pos, isWhite, id);
    pawns.push_back(pawn);
    pieces.push_back(pawn);
}

void Pawn::Make(char file, int rank, bool isWhite, int id)
{
    Vector2 pos = ChessNotation::CharIntToVec(file, rank);
    
    Make(pos, isWhite, id);
}

void Pawn::Update()
{ 
    Piece::Update(); 
    
    availablePositions.clear();
    
    int yDir = isWhite ? -1 : 1;
    
    availablePositions.push_back({pos.x, pos.y + yDir});
    if((isWhite && pos.y == 6) || (!isWhite && pos.y == 1))
    {
        availablePositions.push_back({pos.x, pos.y + (yDir * 2)});
    }
    
    Piece::RemoveBlockedPositions(this);
}

void Pawn::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}