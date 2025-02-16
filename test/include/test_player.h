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

void HumanPlayerMove_BackMove_MoveConditions();

void HumanPlayerMove_MoveBecameKing_MoveConditions();

void HumanPlayerMove_EatBecameKingSimple_MoveConditions();

void HumanPlayerMove_DoubleMoveKing_MoveConditions();

void HumanPlayerMove_LongMoveEatKing_MoveConditions();

void HumanPlayerMove_MoveBecameKing_ResetCounter();

void HumanPlayerMove_MoveBecameKing_SetHumanHasKing();

void HumanPlayerMove_SimpleEat_ResetCounter();

void HumanPlayerMove_SimpleEat_ResetComputerHasKing();

void HumanPlayerMove_UselessMove_IncrementCounter();

void HumanPlayerMove_WrongInput_ErrorMessage();

void ComputerPlayerMove_Border_Move();

void ComputerPlayerMove_EmptyBoard_HumanWon();

void ComputerPlayerMove_CantMove_Draw();

void ComputerPlayerMove_SimpleEat_Eat();

void ComputerPlayerMove_DoubleEat_EatTwice();

void ComputerPlayerMove_HightEat_BecameKing();

void ComputerPlayerMove_HightEatAndRepeatLater_EatAll();

void ComputerPlayerMove_HightEat_ResetCounter();

void ComputerPlayerMove_SimpleEat_ResetHumanHasKing();

void ComputerPlayerMove_HightEat_SetComputerHasKing();

void ComputerPlayerMove_UselessMove_IncrementCounter();

void HumanPlayerMove_SimpleMove_MoveConditions();

void HumanPlayerMove_SimpleMoveAnotherFormat_MoveConditions();

#endif // TEST_PLAYER_H
