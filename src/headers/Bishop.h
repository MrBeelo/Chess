#ifndef BISHOP_H
#define BISHOP_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

using namespace std;

class Bishop : public Piece
{
    public:
    Bishop(Vector2 pos, bool isWhite, int id);
    ~Bishop();
    
    static Texture2D textureWhite;
    static Texture2D textureBlack;
    static vector<Bishop*> bishops;
    
    static void LoadContent();
    static void UnloadContent();
    static void Make(Vector2 pos, bool isWhite, int id);
    static void Make(char file, int rank, bool isWhite, int id);
    static void RemovePieceFromVector(Bishop* bishop);
    void Update() override;
    void Draw() override;
    void CalculateBishopMoves();
};

#endif