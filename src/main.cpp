#include "headers/ChessNotation.h"
#include "headers/raylib.h"
#include <cmath>

#include "headers/Board.h"
#include "headers/Pawn.h"
#include "headers/Knight.h"
#include "headers/Bishop.h"
#include "headers/Rook.h"
#include "headers/Queen.h"
#include "headers/King.h"
#include "headers/Piece.h"
#include "headers/Sounds.h"
#include "headers/Globals.h"

#include "headers/resource_dir.h"

using namespace std;

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	Board* board = new Board({8, 8});
	int windowX = Board::tilesize * board->size.x;
	int windowY = Board::tilesize * board->size.y;
	Globals::f3On = false;

	InitWindow(windowX, windowY, "Chess");
	InitAudioDevice();
	
	SearchAndSetResourceDir("assets");

	Sounds::LoadContent();
	Pawn::LoadContent();
	Knight::LoadContent();
	Bishop::LoadContent();
	Rook::LoadContent();
	Queen::LoadContent();
	King::LoadContent();
	
	for(int i = 0; i <= 7; i++)
	{
	    Pawn::Make(ChessNotation::VecToCharInt({(float)i, 2}).first, 2, true, i);
		Pawn::Make(ChessNotation::VecToCharInt({(float)i, 7}).first, 7, false, i + 8);
	}
	
	Knight::Make('B', 1, true, 1);
	Knight::Make('G', 1, true, 2);
	Knight::Make('B', 8, false, 3);
	Knight::Make('G', 8, false, 4);
	
	Bishop::Make('C', 1, true, 1);
	Bishop::Make('F', 1, true, 2);
	Bishop::Make('C', 8, false, 3);
	Bishop::Make('F', 8, false, 4);
	
	Rook::Make('A', 1, true, 1);
	Rook::Make('H', 1, true, 2);
	Rook::Make('A', 8, false, 3);
	Rook::Make('H', 8, false, 4);
	
	Queen::Make('D', 1, true, 1);
	Queen::Make('D', 8, false, 2);
	
	King::Make('E', 1, true, 1);
	King::Make('E', 8, false, 2);

	// game loop
	while (!WindowShouldClose())
	{
	    Globals::Update();
		
        board->Update();
	    for(Piece* piece : Piece::pieces)
		{
		    piece->Update();
		}
		
		BeginDrawing();
		ClearBackground(BLACK);

		board->Draw();
		
		for(Piece* piece : Piece::pieces)
		{
		    piece->Draw(); 
		}

		EndDrawing();
	}
	
	Sounds::UnloadContent();
	Piece::UnloadContent();
	Pawn::UnloadContent();
	Knight::UnloadContent();
	Bishop::UnloadContent();
	Rook::UnloadContent();
	Queen::UnloadContent();
	King::UnloadContent();
	
	delete board;

	CloseWindow();
	return 0;
}
