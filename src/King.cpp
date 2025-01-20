#include "headers/King.h"
#include "headers/Piece.h"
#include "headers/Rook.h"
#include "headers/ChessNotation.h"
#include "headers/raylib.h"
#include <algorithm>

Texture2D King::textureWhite;
Texture2D King::textureBlack;
vector<King*> King::kings;

using namespace std;

King::King(Vector2 pos, bool isWhite, int id) : Piece(PieceType::KING, pos, isWhite, id) {}
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

void King::RemovePieceFromVector(King* king) {
    auto it = remove(kings.begin(), kings.end(), king);
    if (it != kings.end()) {
        kings.erase(it, kings.end()); // Remove the piece from the vector
    }
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
    
    for(Rook* rook : Rook::rooks)
    {
        if(CanCastleShort(this, rook))
        {
            availablePositions.push_back({pos.x + 2, pos.y});
        }
        
        if(CanCastleLong(this, rook))
        {
            availablePositions.push_back({pos.x - 2, pos.y});
        }
    }
    
    Piece::RemoveBlockedPositions(this, false);
}

void King::Draw()
{
    Texture2D texture = isWhite ? textureWhite : textureBlack;
    DrawTexturePro(texture, {0, 0, 150, 150}, rect, {0, 0}, 0, WHITE);
    
    Piece::Draw();
}

bool King::CanCastleShort(King* king, Rook* rook)
{
    pair<char, int> rookPos = ChessNotation::VecToCharInt(rook->pos);
    return !king->hasMoved && !rook->hasMoved && rookPos.first == 'H' && rook->pos.y == king->pos.y;
}

bool King::CanCastleLong(King* king, Rook* rook)
{
    pair<char, int> rookPos = ChessNotation::VecToCharInt(rook->pos);
    return !king->hasMoved && !rook->hasMoved && rookPos.first == 'A' && rook->pos.y == king->pos.y;
}

void King::Castle(Rook* rook)
{
    pair<char, int> rookPos = ChessNotation::VecToCharInt(rook->pos);
    if(rookPos.first == 'H')
    {
        Rook::MoveTo(rook, 'F', rookPos.second, rook->id);
    } else if(rookPos.first == 'A')
    {
        Rook::MoveTo(rook, 'D', rookPos.second, rook->id);
    }
}

bool King::IsChecked()
{
    for(Piece* piece : Piece::pieces)
    {
        for(Vector2 avPosition : piece->availablePositions)
        {
            if(pos.x == avPosition.x && pos.y == avPosition.y && piece->isWhite != isWhite)
            {
                return true;
            }
        }
    }
    
    return false;
}

bool King::IsChecked(Vector2 hypPos)
{
    for(Piece* piece : Piece::pieces)
    {
        for(Vector2 avPosition : piece->availablePositions)
        {
            if(hypPos.x == avPosition.x && hypPos.y == avPosition.y && piece->isWhite != isWhite && piece->pieceType != PieceType::KING)
            {
                return true;
            }
        }
    }
    
    return false;
}

/*bool King::IsMated()
{
    if (!IsChecked()) 
    {
        return false; // Not in check, not mated
    }

    bool hasSafeMove = false; 

    for (Vector2 avPosition : availablePositions) 
    {
        if (!IsChecked(avPosition)) 
        {
            hasSafeMove = true; 
            break; // Break the loop as soon as a safe move is found
        }
    }

    return !hasSafeMove; 
}*/