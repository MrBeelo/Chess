#include "headers/Board.h"
#include "headers/Piece.h"
#include "headers/ChessNotation.h"
#include "headers/Globals.h"
#include "headers/Sounds.h"
#include <algorithm>
#include <cmath>
#include <string>

vector<Piece*> Piece::pieces;

Piece::Piece(Vector2 pos, bool isWhite, int id) : pos(pos), isWhite(isWhite), id(id)
{
    rect = {pos.x * Board::tilesize, pos.y * Board::tilesize, Board::tilesize, Board::tilesize};
}

Piece::~Piece() {}

void Piece::UnloadContent()
{
    for(Piece* piece : pieces)
    {
        delete piece;
    }
}

void Piece::Update()
{
    pos.x = clamp((int)pos.x, 0, 7);
    pos.y = clamp((int)pos.y, 0, 7);
    rect = {pos.x * Board::tilesize, pos.y * Board::tilesize, Board::tilesize, Board::tilesize};
    
    chessPos = ChessNotation::VecToCharInt(pos);
    
    
}

void Piece::Draw()
{
    if(Globals::f3On)
    {
        string posString = "(" + string(1, chessPos.first) + to_string(chessPos.second) + ")";
        DrawText(posString.c_str(), (int)((pos.x * Board::tilesize) + 50), (int)((pos.y * Board::tilesize)), 20, BLACK);
    }
}


//TODO: FIX THIS METHOD
void Piece::CheckAvailablePositions(Piece* piece)
{
    for (Piece* allPieces : pieces) {
        if (allPieces != piece) {
            piece->availablePositions.erase(
                std::remove_if(
                    piece->availablePositions.begin(),
                    piece->availablePositions.end(),
                    [&](const Vector2& avPosition) {
                        return allPieces->pos.x == avPosition.x && allPieces->pos.y == avPosition.y;
                    }),
                piece->availablePositions.end());
        }
    }
}

bool Piece::CanMoveTo(Piece* piece, Vector2 position, int id)
{
    // Check boundaries
    if (position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7) {
        return false;
    }

    // Ensure the piece id matches
    if (piece->id != id) {
        return false;
    }

    // Ensure the target position is not occupied by another piece
    for (Piece* allPieces : pieces) {
        if (allPieces != piece && allPieces->pos.x == position.x && allPieces->pos.y == position.y) {
            return false;
        }
    }
    
    bool found = false;
    for(Vector2 avPosition : piece->availablePositions)
    {
        if (position.x == avPosition.x && position.y == avPosition.y) {
            found = true;
            break;  // Found a match, no need to continue checking
        }
    }

    return found;
}

void Piece::MoveTo(Piece* piece, Vector2 position, int id)
{
    if (CanMoveTo(piece, position, id)) 
    {
        piece->pos.x = position.x;
        piece->pos.y = position.y;
        
        PlaySound(Sounds::moveSelf);
    }
}

void Piece::MoveTo(Piece* piece, char file, int rank, int id)
{
    Vector2 position = ChessNotation::CharIntToVec(file, rank);
    
    if (CanMoveTo(piece, position, id)) 
    {
        piece->pos.x = position.x;
        piece->pos.y = position.y;
        
        PlaySound(Sounds::moveSelf);
    }
}

void Piece::MoveBy(Piece* piece, int x, int y, int id)
{
    float oldX = piece->pos.x;
    float oldY = piece->pos.y;
    
    //TODO Fix this method:
    if (CanMoveTo(piece, {oldX += x, oldY += y}, id)) 
    {
        piece->pos.x += x;
        piece->pos.y += y;
        
        PlaySound(Sounds::moveSelf);
    }
}