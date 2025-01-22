#ifndef KNIGHT_H
#define KNIGHT_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class Knight : public Piece
{
    public:
    Knight(Vector2 pos, bool isWhite, int id);
    ~Knight();
    
    static Texture2D textureWhite;
    static Texture2D textureBlack;
    static vector<Knight*> knights;
    
    static void LoadContent();
    static void UnloadContent();
    static void Make(Vector2 pos, bool isWhite, int id);
    static void Make(char file, int rank, bool isWhite, int id);
    static void RemovePieceFromVector(Knight* knight);
    void Update() override;
    void Draw() override;
    void CalculateKnightMoves();
};

#endif