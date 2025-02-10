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
    return 0;
}
