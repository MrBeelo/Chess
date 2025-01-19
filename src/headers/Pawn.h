#ifndef PAWN_H
#define PAWN_H

#include "raylib.h"
#include "Piece.h"
#include "vector"

class Pawn : public Piece
{
    public:
    Pawn(Vector2 pos, bool isWhite, int id);
    ~Pawn();
    
    static Texture2D textureWhite;
    static Texture2D textureBlack;
    static vector<Pawn*> pawns;
    
    static void LoadContent();
    static void UnloadContent();
    static void Make(Vector2 pos, bool isWhite, int id);
    static void Make(char file, int rank, bool isWhite, int id);
    void Update() override;
    void Draw() override;
    static void PawnSpecials(Pawn* pawn, Piece* otherPiece);
    static void Promotion(Pawn* pawn);
};

#endif