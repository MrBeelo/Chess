#ifndef QUEEN_H
#define QUEEN_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class Queen : public Piece
{
    public:
    Queen(Vector2 pos, bool isWhite, int id);
    ~Queen();
    
    static Texture2D textureWhite;
    static Texture2D textureBlack;
    static vector<Queen*> queens;
    
    static void LoadContent();
    static void UnloadContent();
    static void Make(Vector2 pos, bool isWhite, int id);
    static void Make(char file, int rank, bool isWhite, int id);
    static void RemovePieceFromVector(Queen* queen);
    void Update() override;
    void Draw() override;
};

#endif