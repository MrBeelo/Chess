#include "headers/ChessNotation.h"
#include <utility>

pair<char, int> ChessNotation::VecToCharInt(Vector2 vector2)
{
    char file = 'A' + vector2.x;
    int rank = 8 - vector2.y;
    
    return make_pair(file, rank);
}

Vector2 ChessNotation::CharIntToVec(char file, int rank)
{
    float x = file - 'A';
    float y = 7 - (rank - 1);
    Vector2 position = {x, y};
    
    return position;
}