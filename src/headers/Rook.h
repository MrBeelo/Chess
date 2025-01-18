#ifndef ROOK_H
#define ROOK_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class Rook : public Piece
{
    public:
    Rook(Vector2 pos, bool isWhite, int id);
    ~Rook();
    
    static Texture2D textureWhite;
    static Texture2D textureBlack;
    static vector<Rook*> rooks;
    
    static void LoadContent();
    static void UnloadContent();
    static void Make(Vector2 pos, bool isWhite, int id);
    static void Make(char file, int rank, bool isWhite, int id);
    void Update() override;
    void Draw() override;
};

#endif