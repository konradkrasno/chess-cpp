#include "UpdateAttributes.h"

UpdateAttributes::UpdateAttributes()
{
}

UpdateAttributes::~UpdateAttributes()
{
}

bool UpdateAttributes::LookForPossibleMoveAndUpdateReactionBoard(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string const actualPosition,
    string const possiblePosition,
    ChessMan const movedChessMan
)
{
    ChessMan checkedField(boardState.at(possiblePosition));
    std::list<string>& possibleMoves(movesBoard.at(actualPosition));
    if (checkedField.GetType() != ChessManType::None)
    {
        if (checkedField.GetColor() == movedChessMan.GetColor()) return true;

        possibleMoves.push_back(possiblePosition);
        UpdateReactionBoard(reactionBoard, possiblePosition, movedChessMan);
        return true;
    }
    possibleMoves.push_back(possiblePosition);
    UpdateReactionBoard(reactionBoard, possiblePosition, movedChessMan);
    return false;
}

void UpdateAttributes::UpdateReactionBoard(
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string const possiblePosition,
    ChessMan const movedChessMan
)
{
    std::list<ChessMan>& fields(reactionBoard.at(possiblePosition));
    fields.push_back(movedChessMan);
}
