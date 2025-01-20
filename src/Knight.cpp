#include "headers/Knight.h"
#include "headers/ChessNotation.h"
#include "headers/Piece.h"
#include <algorithm>

Texture2D Knight::textureWhite;
Texture2D Knight::textureBlack;
vector<Knight*> Knight::knights;

Knight::Knight(Vector2 pos, bool isWhite, int id) : Piece(PieceType::KNIGHT, pos, isWhite, id) {}
Knight::~Knight() {}

void Knight::LoadContent()
{
    textureWhite = LoadTexture("sprites/wn.png");
    textureBlack = LoadTexture("sprites/bn.png");
}

void Knight::UnloadContent()
{
    UnloadTexture(textureWhite);
    UnloadTexture(textureBlack);
    for(Knight* knight : knights)
    {
        delete knight;
    }
}

void Knight::Make(Vector2 pos, bool isWhite, int id)
{
    Knight* knight = new Knight(pos, isWhite, id);
    knights.push_back(knight);
    pieces.push_back(knight);
}

void Knight::Make(char file, int rank, bool isWhite, int id)
{
    Vector2 pos = ChessNotation::CharIntToVec(file, rank);
    
    Make(pos, isWhite, id);
}

void Knight::RemovePieceFromVector(Knight* knight) {
    auto it = remove(knights.begin(), knights.end(), knight);
    if (it != knights.end()) {
        knights.erase(it, knights.end()); // Remove the piece from the vector
    }
}

void Knight::Update()
{ 
    Piece::Update(); 
    
    availablePositions.clear();
    
    availablePositions.push_back({pos.x + 1, pos.y + 2});
    availablePositions.push_back({pos.x + -1, pos.y + 2});
    availablePositions.push_back({pos.x + 1, pos.y + -2});
    availablePositions.push_back({pos.x + -1, pos.y + -2});
    availablePositions.push_back({pos.x + 2, pos.y + 1});
    availablePositions.push_back({pos.x + -2, pos.y + 1});
    availablePositions.push_back({pos.x + 2, pos.y + -1});
    availablePositions.push_back({pos.x + -2, pos.y + -1});
    
    Piece::RemoveBlockedPositions(this, true);
}

void Knight::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}