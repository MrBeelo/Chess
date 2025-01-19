#include "headers/Pawn.h"
#include "headers/Queen.h"
#include "headers/ChessNotation.h"

Texture2D Pawn::textureWhite;
Texture2D Pawn::textureBlack;
vector<Pawn*> Pawn::pawns;

Pawn::Pawn(Vector2 pos, bool isWhite, int id) : Piece(PieceType::PAWN, pos, isWhite, id) {}
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
    
    AddPosition(this, pos.x, pos.y + yDir);
    if((isWhite && pos.y == 6) || (!isWhite && pos.y == 1))
    {
        AddPosition(this, pos.x, pos.y + (yDir * 2));
    }
    
    Piece::RemoveBlockedPositions(this, false);
    
    for(Piece* otherPiece : Piece::pieces)
    {
        PawnSpecials(this, otherPiece);
    }
    
    Promotion(this);
}

void Pawn::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}

void Pawn::PawnSpecials(Pawn* pawn, Piece* otherPiece)
{
    int yDir = pawn->isWhite ? -1 : 1;
    
    if(otherPiece->pos.x == pawn->pos.x && otherPiece->pos.y == pawn->pos.y + yDir)
    {
        Piece::RemovePosition(pawn, otherPiece->pos.x, otherPiece->pos.y);
    }
    
    if(otherPiece->pos.x == pawn->pos.x + 1 && otherPiece->pos.y == pawn->pos.y + yDir)
    {
        Piece::AddPosition(pawn, otherPiece->pos.x, otherPiece->pos.y);
    }
    
    if(otherPiece->pos.x == pawn->pos.x - 1 && otherPiece->pos.y == pawn->pos.y + yDir)
    {
        Piece::AddPosition(pawn, otherPiece->pos.x, otherPiece->pos.y);
    }
    
    if(otherPiece->isWhite == pawn->isWhite)
    {
        RemovePosition(pawn, otherPiece->pos.x, otherPiece->pos.y);
    }
}

void Pawn::Promotion(Pawn* pawn)
{
    if((pawn->isWhite && ChessNotation::VecToCharInt(pawn->pos).second == 8) || (!pawn->isWhite && ChessNotation::VecToCharInt(pawn->pos).second == 1))
    {
        bool isPromoWhite = pawn->isWhite;
        Vector2 promoPos = pawn->pos;
        Piece::DeletePiece(pawn);
        Queen::Make(promoPos, isPromoWhite, Queen::queens.size() + 1);
    }
}