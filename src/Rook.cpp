#include "headers/Rook.h"
#include "headers/ChessNotation.h"
#include <algorithm>

Texture2D Rook::textureWhite;
Texture2D Rook::textureBlack;
vector<Rook*> Rook::rooks;

Rook::Rook(Vector2 pos, bool isWhite, int id) : Piece(PieceType::ROOK, pos, isWhite, id) {}
Rook::~Rook() {}

void Rook::LoadContent()
{
    textureWhite = LoadTexture("sprites/wr.png");
    textureBlack = LoadTexture("sprites/br.png");
}

void Rook::UnloadContent()
{
    UnloadTexture(textureWhite);
    UnloadTexture(textureBlack);
    for(Rook* rook : rooks)
    {
        delete rook;
    }
}

void Rook::Make(Vector2 pos, bool isWhite, int id)
{
    Rook* rook = new Rook(pos, isWhite, id);
    rooks.push_back(rook);
    pieces.push_back(rook);
}

void Rook::Make(char file, int rank, bool isWhite, int id)
{
    Vector2 pos = ChessNotation::CharIntToVec(file, rank);
    
    Make(pos, isWhite, id);
}

void Rook::RemovePieceFromVector(Rook* rook) {
    auto it = remove(rooks.begin(), rooks.end(), rook);
    if (it != rooks.end()) {
        rooks.erase(it, rooks.end()); // Remove the piece from the vector
    }
}

void Rook::Update()
{ 
    Piece::Update(); 
    
    CalculateAvailablePositions();
}

void Rook::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}

void Rook::CalculateRookMoves()
{
    for(int i = 1; i < 8; i++)
    {
        availablePositions.push_back({pos.x + i, pos.y});
        availablePositions.push_back({pos.x + -i, pos.y});
        availablePositions.push_back({pos.x, pos.y + i});
        availablePositions.push_back({pos.x, pos.y + -i});
    }
    
    Piece::RemoveBlockedPositions(this, false);
}