#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include "Board.h"
#include "vector"

using namespace std;

class Piece
{
    public:
    Vector2 pos;
    pair<char, int> chessPos;
    Rectangle rect = {pos.x * Board::tilesize, pos.y * Board::tilesize, 75, 75};
    bool isWhite;
    int id;
    static vector<Piece*> pieces;
    vector<Vector2> availablePositions;
    
    Piece(Vector2 pos, bool isWhite, int id);
    virtual ~Piece();
    
    static void UnloadContent();
    virtual void Update();
    virtual void Draw();
    static void RemoveBlockedPositions(Piece* piece);
    static void RemovePositionsInDirection(Piece* piece, Piece* otherPiece, int yDirection, int xDirection);
    static void RemovePosition(Piece* piece, int x, int y);
    static bool CanMoveTo(Piece* piece, Vector2 position, int id);
    static void MoveTo(Piece* piece, Vector2 position, int id);
    static void MoveTo(Piece* piece, char file, int rank, int id);
    static void MoveBy(Piece* piece, int x, int y, int id);
};

#endif