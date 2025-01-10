#include "raylib.h"
#include <cmath>

#include "headers/Board.h"
#include "headers/Pawn.h"
#include "headers/Piece.h"
#include "headers/Sounds.h"

#include "headers/resource_dir.h"

using namespace std;

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	Board* board = new Board({8, 8});
	int windowX = Board::tilesize * board->size.x;
	int windowY = Board::tilesize * board->size.y;

	InitWindow(windowX, windowY, "Chess");
	InitAudioDevice();
	
	SearchAndSetResourceDir("assets");

	Sounds::LoadContent();
	Pawn::LoadContent();
	
	Pawn::Make({3, 3}, true, 1);
	Pawn::Make('H', 8, false, 2);

	// game loop
	while (!WindowShouldClose())
	{
        board->Update();
	    for(Piece* piece : Piece::pieces)
		{
		    piece->Update();
		}

		if(IsKeyPressed(KEY_P))
		{
		    for(Piece* piece : Piece::pieces)
			{
			    Piece::MoveBy(piece, 1, 1, 1);
			}
		}
		
		if(IsKeyPressed(KEY_K))
		{
		    for(Piece* piece : Piece::pieces)
			{
			    Piece::MoveBy(piece, 0, 1, 2);
			}
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
	Pawn::UnloadContent();

	CloseWindow();
	return 0;
}
