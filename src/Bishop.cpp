#include "headers/Bishop.h"
#include "headers/ChessNotation.h"

Texture2D Bishop::textureWhite;
Texture2D Bishop::textureBlack;
vector<Bishop*> Bishop::bishops;

Bishop::Bishop(Vector2 pos, bool isWhite, int id) : Piece(pos, isWhite, id) {}
Bishop::~Bishop() {}

void Bishop::LoadContent()
{
    textureWhite = LoadTexture("sprites/wb.png");
    textureBlack = LoadTexture("sprites/bb.png");
}

void Bishop::UnloadContent()
{
    UnloadTexture(textureWhite);
    UnloadTexture(textureBlack);
    for(Bishop* bishop : bishops)
    {
        delete bishop;
    }
}

void Bishop::Make(Vector2 pos, bool isWhite, int id)
{
    Bishop* bishop = new Bishop(pos, isWhite, id);
    bishops.push_back(bishop);
    pieces.push_back(bishop);
}

void Bishop::Make(char file, int rank, bool isWhite, int id)
{
    Vector2 pos = ChessNotation::CharIntToVec(file, rank);
    
    Make(pos, isWhite, id);
}

void Bishop::Update()
{ 
    Piece::Update(); 
    
    availablePositions.clear();
    
    for(int i = 1; i < 8; i++)
    {
        availablePositions.push_back({pos.x + i, pos.y + i});
        availablePositions.push_back({pos.x + i, pos.y + -i});
        availablePositions.push_back({pos.x + -i, pos.y + i});
        availablePositions.push_back({pos.x + -i, pos.y + -i});
    }
    
    Piece::RemoveBlockedPositions(this, false);
}

void Bishop::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}