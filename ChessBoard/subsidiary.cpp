#include "subsidiary.h"
#include "ChessMan.h"

string ConvertFileRandToPosition(char file, char rank)
{
    string position;
    position += file;
    position += rank;
    return position;
}
