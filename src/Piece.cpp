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

void Piece::RemoveBlockedPositions(Piece* piece, bool noclip) {
    for (Piece* otherPiece : pieces) {
        if (otherPiece != piece) {
            if(!noclip)
            {
                if (otherPiece->pos.x == piece->pos.x && otherPiece->pos.y > piece->pos.y) { // Up
                    // Remove positions above
                    RemovePositionsInDirection(piece, otherPiece, 1, 0); 
                } 
                
                if (otherPiece->pos.x == piece->pos.x && otherPiece->pos.y < piece->pos.y) { // Down
                    // Remove positions below
                    RemovePositionsInDirection(piece, otherPiece, -1, 0); 
                } 
                
                if (otherPiece->pos.y == piece->pos.y && otherPiece->pos.x > piece->pos.x) { // Right
                    // Remove positions to the right
                    RemovePositionsInDirection(piece, otherPiece, 0, 1); 
                } 
                
                if (otherPiece->pos.y == piece->pos.y && otherPiece->pos.x < piece->pos.x) { // Left
                    // Remove positions to the left
                    RemovePositionsInDirection(piece, otherPiece, 0, -1); 
                } 
                
                if (otherPiece->pos.x > piece->pos.x && otherPiece->pos.y > piece->pos.y) { // Up-Right
                    // Remove positions up-right
                    RemovePositionsInDirection(piece, otherPiece, 1, 1); 
                } 
                
                if (otherPiece->pos.x > piece->pos.x && otherPiece->pos.y < piece->pos.y) { // Down-Right
                    // Remove positions down-right
                    RemovePositionsInDirection(piece, otherPiece, -1, 1); 
                } 
                
                if (otherPiece->pos.x < piece->pos.x && otherPiece->pos.y > piece->pos.y) { // Up-Left
                    // Remove positions up-left
                    RemovePositionsInDirection(piece, otherPiece, 1, -1); 
                } 
                
                if (otherPiece->pos.x < piece->pos.x && otherPiece->pos.y < piece->pos.y) { // Down-Left
                    // Remove positions down-left
                    RemovePositionsInDirection(piece, otherPiece, -1, -1); 
                }
            }

            if(otherPiece->isWhite == piece->isWhite)
            {
                RemovePosition(piece, otherPiece->pos.x, otherPiece->pos.y);
            }
        }
    }
}

void Piece::RemovePositionsInDirection(Piece* piece, Piece* otherPiece, int yDirection, int xDirection) {
    for (int i = 1; i < 8; i++)
    {
        RemovePosition(piece, otherPiece->pos.x + (xDirection * i), otherPiece->pos.y + (yDirection * i));
    }
}

void Piece::AddPosition(Piece* piece, int x, int y) {
    piece->availablePositions.push_back({(float)x, (float)y});
}

void Piece::RemovePosition(Piece* piece, int x, int y) {
    // Iterate through available positions to find and remove the specified position
    for (auto it = piece->availablePositions.begin(); it != piece->availablePositions.end(); ++it) {
        // Compare the position with the current position (x, y)
        if (it->x == x && it->y == y) {
            // Remove the position from the list
            piece->availablePositions.erase(it);
            return;  // Exit after removing the first match
        }
    }
}

void Piece::RemovePieceFromVector(Piece* piece) {
    auto it = std::remove(pieces.begin(), pieces.end(), piece);
    if (it != pieces.end()) {
        pieces.erase(it, pieces.end()); // Remove the piece from the vector
    }
}

bool Piece::CanMoveTo(Piece* piece, Vector2 position, int id)
{
    if (position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7) {
        return false;
    }

    if (piece->id != id) {
        return false;
    }

    bool found = false;
    for (Vector2 avPosition : piece->availablePositions) {
        if (position.x == avPosition.x && position.y == avPosition.y) {
            found = true;
            break;
        }
    }
    if (!found) {
        return false;
    }

    for (Piece* otherPiece : pieces) {
        if (otherPiece != piece && otherPiece->pos.x == position.x && otherPiece->pos.y == position.y) {
            if (otherPiece->isWhite != piece->isWhite) {
                DeletePiece(otherPiece);
                return true;
            } else {
                return false;
            }
        }
    }

    return true;
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

void Piece::DeletePiece(Piece* piece)
{
    RemovePieceFromVector(piece);
    delete piece;
}

void Piece::DeletePiece(Vector2 pos)
{
    for(Piece* piece : pieces)
    {
        if(piece->pos.x == pos.x && piece->pos.y == pos.y)
        {
            DeletePiece(piece);
        }
    }
}

void Piece::DeletePiece(char file, int rank)
{
    for(Piece* piece : pieces)
    {
        Vector2 pos = ChessNotation::CharIntToVec(file, rank);
        
        if(piece->pos.x == pos.x && piece->pos.y == pos.y)
        {
            DeletePiece(piece);
        }
    }
}