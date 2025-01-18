#include "headers/Queen.h"
#include "headers/ChessNotation.h"

Texture2D Queen::textureWhite;
Texture2D Queen::textureBlack;
vector<Queen*> Queen::queens;

Queen::Queen(Vector2 pos, bool isWhite, int id) : Piece(pos, isWhite, id) {}
Queen::~Queen() {}

void Queen::LoadContent()
{
    textureWhite = LoadTexture("sprites/wq.png");
    textureBlack = LoadTexture("sprites/bq.png");
}

void Queen::UnloadContent()
{
    UnloadTexture(textureWhite);
    UnloadTexture(textureBlack);
    for(Queen* queen : queens)
    {
        delete queen;
    }
}

void Queen::Make(Vector2 pos, bool isWhite, int id)
{
    Queen* queen = new Queen(pos, isWhite, id);
    queens.push_back(queen);
    pieces.push_back(queen);
}

void Queen::Make(char file, int rank, bool isWhite, int id)
{
    Vector2 pos = ChessNotation::CharIntToVec(file, rank);
    
    Make(pos, isWhite, id);
}

void Queen::Update()
{ 
    Piece::Update(); 
    
    availablePositions.clear();
    
    for(int i = 1; i < 8; i++)
    {
        availablePositions.push_back({pos.x + i, pos.y});
        availablePositions.push_back({pos.x + -i, pos.y});
        availablePositions.push_back({pos.x, pos.y + i});
        availablePositions.push_back({pos.x, pos.y + -i});
        availablePositions.push_back({pos.x + i, pos.y + i});
        availablePositions.push_back({pos.x + i, pos.y + -i});
        availablePositions.push_back({pos.x + -i, pos.y + i});
        availablePositions.push_back({pos.x + -i, pos.y + -i});
    }
    
    Piece::RemoveBlockedPositions(this, false);
}

void Queen::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}