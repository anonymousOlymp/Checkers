#include "position.h"
#include "test_board.h"
#include "test_checker.h"
#include "test_game.h"
#include "test_player.h"
#include "test_position.h"

int main(int argc, const char** argv) {
    PositionFromString_VariousString_ReturnPosition("abcdef", false);
    PositionFromString_VariousString_ReturnPosition("ab", false);
    PositionFromString_VariousString_ReturnPosition("A9", false);
    PositionFromString_VariousString_ReturnPosition("V3", false);
    PositionFromString_VariousString_ReturnPosition("A1", true);
    PositionFromString_VariousString_ReturnPosition("H8", true);
    PositionFromString_VariousString_ReturnPosition("C5", true);

    PositionEquality_VariousPosition_ReturnExpected("A1", "A1", true);
    PositionEquality_VariousPosition_ReturnExpected("C5", "C5", true);
    PositionEquality_VariousPosition_ReturnExpected("A1", "A4", false);
    PositionEquality_VariousPosition_ReturnExpected("A1", "B1", false);

    MoveToDirection_DiagonalMove_ReturnExpected("A1", "B2",
                                                Direction::UP_RIGHT);
    MoveToDirection_DiagonalMove_ReturnExpected("A1", "E5",
                                                Direction::UP_RIGHT);
    MoveToDirection_DiagonalMove_ReturnExpected("B2", "A1",
                                                Direction::DOWN_LEFT);
    MoveToDirection_DiagonalMove_ReturnExpected("E5", "A1",
                                                Direction::DOWN_LEFT);
    MoveToDirection_DiagonalMove_ReturnExpected("B2", "A3", Direction::UP_LEFT);
    MoveToDirection_DiagonalMove_ReturnExpected("E5", "A7", Direction::UP_LEFT);
    MoveToDirection_DiagonalMove_ReturnExpected("A3", "B2",
                                                Direction::DOWN_RIGHT);
    MoveToDirection_DiagonalMove_ReturnExpected("A7", "E5",
                                                Direction::DOWN_RIGHT);

    MoveToDirection_StraightMove_ThrowsLogicError("A1", "A4");
    MoveToDirection_StraightMove_ThrowsLogicError("A1", "D1");
    MoveToDirection_StraightMove_ThrowsLogicError("A1", "A1");

    PositionAdd_CorrectDirection_ReturnsExpectedPosition("E4", "D5",
                                                         Direction::UP_LEFT);
    PositionAdd_CorrectDirection_ReturnsExpectedPosition("E4", "F5",
                                                         Direction::UP_RIGHT);
    PositionAdd_CorrectDirection_ReturnsExpectedPosition("E4", "D3",
                                                         Direction::DOWN_LEFT);
    PositionAdd_CorrectDirection_ReturnsExpectedPosition("E4", "F3",
                                                         Direction::DOWN_RIGHT);

    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "C1", Direction::DOWN_RIGHT, "Error. Can't move DOWN_RIGHT!");
    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "C1", Direction::DOWN_LEFT, "Error. Can't move DOWN_LEFT!");
    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "C8", Direction::UP_RIGHT, "Error. Can't move UP_RIGHT!");
    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "C8", Direction::UP_LEFT, "Error. Can't move UP_LEFT!");
    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "A4", Direction::DOWN_LEFT, "Error. Can't move DOWN_LEFT!");
    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "A4", Direction::UP_LEFT, "Error. Can't move UP_LEFT!");
    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "H4", Direction::DOWN_RIGHT, "Error. Can't move DOWN_RIGHT!");
    PositionAdd_IncorrectDirection_ThrowsLogicError(
        "H4", Direction::UP_RIGHT, "Error. Can't move UP_RIGHT!");

    ApplyIfExists_VariousDirection_ReturnsExpected("C5", Direction::UP_RIGHT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("C5", Direction::UP_LEFT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("C5", Direction::DOWN_RIGHT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("C5", Direction::DOWN_LEFT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("A5", Direction::UP_RIGHT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("A5", Direction::UP_LEFT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("A5", Direction::DOWN_RIGHT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("A5", Direction::DOWN_LEFT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("H5", Direction::UP_RIGHT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("H5", Direction::UP_LEFT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("H5", Direction::DOWN_RIGHT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("H5", Direction::DOWN_LEFT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("C1", Direction::UP_RIGHT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("C1", Direction::UP_LEFT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("C1", Direction::DOWN_RIGHT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("C1", Direction::DOWN_LEFT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("C8", Direction::UP_RIGHT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("C8", Direction::UP_LEFT,
                                                   false);
    ApplyIfExists_VariousDirection_ReturnsExpected("C8", Direction::DOWN_RIGHT,
                                                   true);
    ApplyIfExists_VariousDirection_ReturnsExpected("C8", Direction::DOWN_LEFT,
                                                   true);

    Exists_VariousDirection_ReturnsExpected("C5", Direction::UP_RIGHT, true);
    Exists_VariousDirection_ReturnsExpected("C5", Direction::UP_LEFT, true);
    Exists_VariousDirection_ReturnsExpected("C5", Direction::DOWN_RIGHT, true);
    Exists_VariousDirection_ReturnsExpected("C5", Direction::DOWN_LEFT, true);
    Exists_VariousDirection_ReturnsExpected("A5", Direction::UP_RIGHT, true);
    Exists_VariousDirection_ReturnsExpected("A5", Direction::UP_LEFT, false);
    Exists_VariousDirection_ReturnsExpected("A5", Direction::DOWN_RIGHT, true);
    Exists_VariousDirection_ReturnsExpected("A5", Direction::DOWN_LEFT, false);
    Exists_VariousDirection_ReturnsExpected("H5", Direction::UP_RIGHT, false);
    Exists_VariousDirection_ReturnsExpected("H5", Direction::UP_LEFT, true);
    Exists_VariousDirection_ReturnsExpected("H5", Direction::DOWN_RIGHT, false);
    Exists_VariousDirection_ReturnsExpected("H5", Direction::DOWN_LEFT, true);
    Exists_VariousDirection_ReturnsExpected("C1", Direction::UP_RIGHT, true);
    Exists_VariousDirection_ReturnsExpected("C1", Direction::UP_LEFT, true);
    Exists_VariousDirection_ReturnsExpected("C1", Direction::DOWN_RIGHT, false);
    Exists_VariousDirection_ReturnsExpected("C1", Direction::DOWN_LEFT, false);
    Exists_VariousDirection_ReturnsExpected("C8", Direction::UP_RIGHT, false);
    Exists_VariousDirection_ReturnsExpected("C8", Direction::UP_LEFT, false);
    Exists_VariousDirection_ReturnsExpected("C8", Direction::DOWN_RIGHT, true);
    Exists_VariousDirection_ReturnsExpected("C8", Direction::DOWN_LEFT, true);

    CheckerToChar_VariousChecker_ReturnsExpected('W', false, 'W');
    CheckerToChar_VariousChecker_ReturnsExpected('B', false, 'B');
    CheckerToChar_VariousChecker_ReturnsExpected('W', true, 'X');
    CheckerToChar_VariousChecker_ReturnsExpected('B', true, 'Y');

    // board
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("A1", true, 'W');
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("A3", true, 'W');
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("B2", true, 'W');
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("H8", true, 'B');
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("H6", true, 'B');
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("G7", true, 'B');
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("B1", false);
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("G8", false);
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("H1", false);
    BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere("C5", false);

    BoardToString_BeginingHumanWhite_ReturnsString();
    BoardToString_BeginingHumanBlack_ReturnsString();
    BoardToString_HumanBlackKingInPosition_ReturnsString();
    BoardToString_HumanBlackWhiteKingInPosition_ReturnsString();

    BoardGetState_AfterInit_ReturnsDefault();

    BoardProcessHumanCheckers_NoValues_NoResult('W');
    BoardProcessHumanCheckers_NoValues_NoResult('B');
    BoardProcessHumanCheckers_OppositeValues_NoResult('W');
    BoardProcessHumanCheckers_OppositeValues_NoResult('B');
    BoardProcessHumanCheckers_ManyValues_ResultHuman('W');
    BoardProcessHumanCheckers_ManyValues_ResultHuman('B');

    BoardProcessComputerCheckers_NoValues_NoResult('W');
    BoardProcessComputerCheckers_NoValues_NoResult('B');
    BoardProcessComputerCheckers_OppositeValues_NoResult('W');
    BoardProcessComputerCheckers_OppositeValues_NoResult('B');
    BoardProcessComputerCheckers_TrueValues_ProcessResult('W');
    BoardProcessComputerCheckers_TrueValues_ProcessResult('B');

    BoardHasHumanChecker_NoChecker_ReturnsFalse('W');
    BoardHasHumanChecker_NoChecker_ReturnsFalse('B');
    BoardHasHumanChecker_OppositeChecker_ReturnsFalse('W');
    BoardHasHumanChecker_OppositeChecker_ReturnsFalse('B');
    BoardHasHumanChecker_HumanChecker_ReturnsTrue('W');
    BoardHasHumanChecker_HumanChecker_ReturnsTrue('B');

    BoardHasComputerChecker_NoChecker_ReturnsFalse('W');
    BoardHasComputerChecker_NoChecker_ReturnsFalse('B');
    BoardHasComputerChecker_OppositeChecker_ReturnsFalse('W');
    BoardHasComputerChecker_OppositeChecker_ReturnsFalse('B');
    BoardHasComputerChecker_HumanChecker_ReturnsTrue('W');
    BoardHasComputerChecker_HumanChecker_ReturnsTrue('B');

    BoardGetFreeMoves_CenterFree_ReturnsAll();
    BoardGetFreeMoves_CornerFree_ReturnsOne();
    BoardGetFreeMoves_NotFree_ReturnsThree('W');
    BoardGetFreeMoves_NotFree_ReturnsThree('B');

    BoardGetFreeMovesBool_CenterFree_ReturnsTwo();
    BoardGetFreeMovesBool_CornerFreeWhite_ReturnsOne();
    BoardGetFreeMovesBool_CornerFreeBlack_ReturnsOne();
    BoardGetFreeMovesBool_NotFree_ReturnsOne('W');
    BoardGetFreeMovesBool_NotFree_ReturnsOne('B');

    BoardGetFreeMovesKing_CenterFree_ReturnsEleven();
    BoardGetFreeMovesKing_CornerFree_ReturnsSeven();
    BoardGetFreeMovesKing_NotFree_ReturnsZero('W');
    BoardGetFreeMovesKing_NotFree_ReturnsZero('B');

    BoardGetEatMoves_CenterFree_ReturnsNone();
    BoardGetEatMoves_CenterWithSameChecker_ReturnsNone();
    BoardGetEatMoves_CenterWithOppositeChecker_ReturnsOne();
    BoardGetEatMoves_CenterWithTwoOppositeChecker_ReturnsNone();
    BoardGetEatMoves_CenterWithTwoChecker_ReturnsNone();
    BoardGetEatMoves_CornerWithOppositeChecker_ReturnsNone();
    BoardGetEatMoves_CenterWithOppositeCheckerForComputer_ReturnsNone();

    BoardGetKingEatMoves_CenterFree_ReturnsNone();
    BoardGetKingEatMoves_CenterWithSameChecker_ReturnsNone();
    BoardGetKingEatMoves_CenterWithOppositeChecker_ReturnsOne();
    BoardGetKingEatMoves_CenterWithTwoOppositeChecker_ReturnsNone();
    BoardGetKingEatMoves_CenterWithTwoChecker_ReturnsNone();
    BoardGetKingEatMoves_CornerWithOppositeChecker_ReturnsNone();
    BoardGetKingEatMoves_CenterWithSameCheckerFarAway_ReturnsNone();
    BoardGetKingEatMoves_CenterWithOppositeCheckerFarAway_ReturnsOne();
    BoardGetKingEatMoves_CenterWithTwoOppositeCheckerFarAway_ReturnsNone();
    BoardGetKingEatMoves_CenterWithTwoCheckerFarAway_ReturnsNone();
    BoardGetKingEatMoves_CornerWithOppositeCheckerFarAway_ReturnsNone();
    BoardGetKingEatMoves_CenterWithOppositeCheckerForComputer_ReturnsNone();

    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "C5", 'W', true, false);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "C5", 'B', true, false);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "C5", 'W', false, false);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "C5", 'B', false, false);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "D8", 'W', true, true);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "D8", 'B', true, false);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "E1", 'W', true, false);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "E1", 'B', true, true);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "D8", 'W', false, false);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "D8", 'B', false, true);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "E1", 'W', false, true);
    BoardIsChangedToKing_VariousPositionOrientationSide_ReturnsExpected(
        "E1", 'B', false, false);
    

    // player
    HumanPlayerMove_EmptyBoard_ComputerWinConditions();
    HumanPlayerMove_CannotMove_DrawConditions();
    HumanPlayerMove_UselessMoves_DrawConditions();
    HumanPlayerMove_SimpleMove_MoveConditions();
    HumanPlayerMove_StraightMove_MoveConditions();
    HumanPlayerMove_MoveGhost_MoveConditions();
    HumanPlayerMove_SimpleMoveAnotherFormat_MoveConditions();
    HumanPlayerMove_DoubleMove_MoveConditions();
    HumanPlayerMove_SimpleEat_MoveConditions();
    HumanPlayerMove_SimpleEatWrongMoving_MoveConditions();
    HumanPlayerMove_MultipleEat_MoveConditions();
    HumanPlayerMove_MultipleEatAndReturns_MoveConditions();
    HumanPlayerMove_MoveThrough_MoveConditions();
    HumanPlayerMove_BackMove_MoveConditions();
    HumanPlayerMove_MoveBecameKing_MoveConditions();
    HumanPlayerMove_EatBecameKingSimple_MoveConditions();
    HumanPlayerMove_DoubleMoveKing_MoveConditions();
    HumanPlayerMove_LongMoveEatKing_MoveConditions();
    HumanPlayerMove_MoveBecameKing_ResetCounter();
    HumanPlayerMove_MoveBecameKing_SetHumanHasKing();
    HumanPlayerMove_SimpleEat_ResetCounter();
    HumanPlayerMove_SimpleEat_ResetComputerHasKing();
    HumanPlayerMove_UselessMove_IncrementCounter();
    HumanPlayerMove_WrongInput_ErrorMessage();

    ComputerPlayerMove_Border_Move();
    ComputerPlayerMove_EmptyBoard_HumanWon();
    ComputerPlayerMove_CantMove_Draw();
    ComputerPlayerMove_SimpleEat_Eat();
    ComputerPlayerMove_DoubleEat_EatTwice();
    ComputerPlayerMove_HightEat_BecameKing();
    ComputerPlayerMove_HightEatAndRepeatLater_EatAll();
    ComputerPlayerMove_HightEat_ResetCounter();
    ComputerPlayerMove_SimpleEat_ResetHumanHasKing();
    ComputerPlayerMove_HightEat_SetComputerHasKing();
    ComputerPlayerMove_UselessMove_IncrementCounter();
    return 0;
}
