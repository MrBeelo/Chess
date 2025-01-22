#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include "Board.h"
#include "PieceType.h"
#include "vector"

using namespace std;

class Piece
{
    public:
    PieceType pieceType;
    Vector2 pos;
    pair<char, int> chessPos;
    Rectangle rect = {pos.x * Board::tilesize, pos.y * Board::tilesize, 75, 75};
    bool isWhite;
    int id;
    bool hasMoved = false;
    static vector<Piece*> pieces;
    vector<Vector2> availablePositions;
    
    Piece(PieceType type, Vector2 pos, bool isWhite, int id);
    virtual ~Piece();
    
    static void UnloadContent();
    virtual void Update();
    virtual void Draw();
    static void RemoveBlockedPositions(Piece* piece, bool noclip);
    static void RemovePositionsInDirection(Piece* piece, Piece* otherPiece, int yDirection, int xDirection);
    static void AddPosition(Piece* piece, int x, int y);
    static void RemovePosition(Piece* piece, int x, int y);
    static bool CanMoveTo(Piece* piece, Vector2 position);
    static void MoveTo(Piece* piece, Vector2 position, int id);
    static void MoveTo(Piece* piece, char file, int rank, int id);
    static void MoveBy(Piece* piece, int x, int y, int id);
    static void RemovePieceFromVector(Piece* piece);
    static void DeletePiece(Piece* piece);
    static void DeletePiece(Vector2 pos);
    static void DeletePiece(char file, int rank);
    void CalculateAvailablePositions();
};

#endif