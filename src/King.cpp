#include "headers/King.h"
#include "headers/ChessNotation.h"

Texture2D King::textureWhite;
Texture2D King::textureBlack;
vector<King*> King::kings;

King::King(Vector2 pos, bool isWhite, int id) : Piece(pos, isWhite, id) {}
King::~King() {}

void King::LoadContent()
{
    textureWhite = LoadTexture("sprites/wk.png");
    textureBlack = LoadTexture("sprites/bk.png");
}

void King::UnloadContent()
{
    UnloadTexture(textureWhite);
    UnloadTexture(textureBlack);
    for(King* king : kings)
    {
        delete king;
    }
}

void King::Make(Vector2 pos, bool isWhite, int id)
{
    King* king = new King(pos, isWhite, id);
    kings.push_back(king);
    pieces.push_back(king);
}

void King::Make(char file, int rank, bool isWhite, int id)
{
    Vector2 pos = ChessNotation::CharIntToVec(file, rank);
    
    Make(pos, isWhite, id);
}

void King::Update()
{ 
    Piece::Update(); 
    
    availablePositions.clear();
    
    availablePositions.push_back({pos.x + 1, pos.y});
    availablePositions.push_back({pos.x + -1, pos.y});
    availablePositions.push_back({pos.x, pos.y + 1});
    availablePositions.push_back({pos.x, pos.y + -1});
    availablePositions.push_back({pos.x + 1, pos.y + 1});
    availablePositions.push_back({pos.x + 1, pos.y + -1});
    availablePositions.push_back({pos.x + -1, pos.y + 1});
    availablePositions.push_back({pos.x + -1, pos.y + -1});
    
    Piece::RemoveBlockedPositions(this, false);
}

void King::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}