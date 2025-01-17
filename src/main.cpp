#include "headers/ChessNotation.h"
#include "headers/raylib.h"
#include <cmath>

#include "headers/Board.h"
#include "headers/Pawn.h"
#include "headers/Knight.h"
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
	
	for(int i = 0; i <= 7; i++)
	{
	    Pawn::Make(ChessNotation::VecToCharInt({(float)i, 2}).first, 2, true, i);
		Pawn::Make(ChessNotation::VecToCharInt({(float)i, 7}).first, 7, false, i + 8);
	}
	
	Knight::Make('B', 1, true, 1);
	Knight::Make('G', 1, true, 2);
	Knight::Make('B', 8, false, 3);
	Knight::Make('G', 8, false, 4);

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
	delete board;

	CloseWindow();
	return 0;
}
