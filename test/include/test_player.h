#ifndef TEST_PLAYER_H
#define TEST_PLAYER_H

void HumanPlayerMove_EmptyBoard_ComputerWinConditions();

void HumanPlayerMove_CannotMove_DrawConditions();

void HumanPlayerMove_UselessMoves_DrawConditions();

void HumanPlayerMove_StraightMove_MoveConditions();

void HumanPlayerMove_DoubleMove_MoveConditions();

void HumanPlayerMove_MoveGhost_MoveConditions();

void HumanPlayerMove_SimpleEat_MoveConditions();

void HumanPlayerMove_SimpleEatWrongMoving_MoveConditions();

void HumanPlayerMove_MultipleEat_MoveConditions();

void HumanPlayerMove_MultipleEatAndReturns_MoveConditions();

void HumanPlayerMove_MoveThrough_MoveConditions();

void HumanPlayerMove_SimpleMove_MoveConditions();

void HumanPlayerMove_SimpleMoveAnotherFormat_MoveConditions();

#endif // TEST_PLAYER_H
