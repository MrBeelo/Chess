#ifndef KING_H
#define KING_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class King : public Piece
{
    public:
    King(Vector2 pos, bool isWhite, int id);
    ~King();
    
    static Texture2D textureWhite;
    static Texture2D textureBlack;
    static vector<King*> kings;
    
    static void LoadContent();
    static void UnloadContent();
    static void Make(Vector2 pos, bool isWhite, int id);
    static void Make(char file, int rank, bool isWhite, int id);
    void Update() override;
    void Draw() override;
};

#endif