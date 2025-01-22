#include "headers/Board.h"
#include "headers/Piece.h"
#include "headers/ChessNotation.h"
#include "headers/Globals.h"
#include "headers/Pawn.h"
#include "headers/Sounds.h"
#include "headers/Pawn.h"
#include "headers/Knight.h"
#include "headers/Bishop.h"
#include "headers/Rook.h"
#include "headers/Queen.h"
#include "headers/King.h"
#include <algorithm>
#include <cmath>
#include <string>

vector<Piece*> Piece::pieces;

Piece::Piece(PieceType type, Vector2 pos, bool isWhite, int id) : pieceType(type), pos(pos), isWhite(isWhite), id(id)
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
    auto it = remove(pieces.begin(), pieces.end(), piece);
    if (it != pieces.end()) {
        pieces.erase(it, pieces.end()); // Remove the piece from the vector
    }
}

bool Piece::CanMoveTo(Piece* piece, Vector2 position)
{
    if (position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7) {
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
    if (CanMoveTo(piece, position)) 
    {
        piece->pos.x = position.x;
        piece->pos.y = position.y;
        
        PlaySound(Sounds::moveSelf);
    }
}

void Piece::MoveTo(Piece* piece, char file, int rank, int id)
{
    Vector2 position = ChessNotation::CharIntToVec(file, rank);
    
    if (CanMoveTo(piece, position)) 
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
    if (CanMoveTo(piece, {oldX += x, oldY += y})) 
    {
        piece->pos.x += x;
        piece->pos.y += y;
        
        PlaySound(Sounds::moveSelf);
    }
}

void Piece::DeletePiece(Piece* piece)
{
    RemovePieceFromVector(piece); // Remove the piece from the generic vector

    // Handle specific piece types
    switch (piece->pieceType)
    {
        case PieceType::PAWN:
        {
            Pawn* pawn = dynamic_cast<Pawn*>(piece);
            if (pawn)
            {
                Pawn::RemovePieceFromVector(pawn);
            }
            break;
        }
        case PieceType::KNIGHT:
        {
            Knight* knight = dynamic_cast<Knight*>(piece);
            if (knight)
            {
                Knight::RemovePieceFromVector(knight);
            }
            break;
        }
        case PieceType::BISHOP:
        {
            Bishop* bishop = dynamic_cast<Bishop*>(piece);
            if (bishop)
            {
                Bishop::RemovePieceFromVector(bishop);
            }
            break;
        }
        case PieceType::ROOK:
        {
            Rook* rook = dynamic_cast<Rook*>(piece);
            if (rook)
            {
                Rook::RemovePieceFromVector(rook);
            }
            break;
        }
        case PieceType::QUEEN:
        {
            Queen* queen = dynamic_cast<Queen*>(piece);
            if (queen)
            {
                Queen::RemovePieceFromVector(queen);
            }
            break;
        }
        case PieceType::KING:
        {
            King* king = dynamic_cast<King*>(piece);
            if (king)
            {
                King::RemovePieceFromVector(king);
            }
            break;
        }
        default:
            // Handle unknown or invalid piece types, if necessary
            break;
    }

    delete piece; // Delete the piece safely
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

void Piece::CalculateAvailablePositions()
{
    availablePositions.clear(); // Clear any previously calculated positions

    // Basic logic: derived classes will override this for specific movement patterns
    switch (pieceType)
    {
        case PieceType::PAWN:
            dynamic_cast<Pawn*>(this)->CalculatePawnMoves();
            break;

        case PieceType::KNIGHT:
            dynamic_cast<Knight*>(this)->CalculateKnightMoves();
            break;

        case PieceType::BISHOP:
            dynamic_cast<Bishop*>(this)->CalculateBishopMoves();
            break;

        case PieceType::ROOK:
            dynamic_cast<Rook*>(this)->CalculateRookMoves();
            break;

        case PieceType::QUEEN:
            dynamic_cast<Queen*>(this)->CalculateQueenMoves();
            break;

        case PieceType::KING:
            dynamic_cast<King*>(this)->CalculateKingMoves();
            break;

        default:
            break;
    }
}
