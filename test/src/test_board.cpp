#include "test_board.h"

#include <algorithm>
#include <unordered_set>

#include "board.h"
#include "checker.h"
#include "position.h"
#include "test.h"

void BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere(
    const std::string &position, bool expected, char type) {
    Position p = Position::from_string(position);

    Board board = Board::create_begining_board();

    assertEquals(board.has_checker(p), expected);
    if (expected) {
        assertEquals(board.get_checker(p), type);
    }
}

void BoardToString_BeginingHumanWhite_ReturnsString() {
    Board board = Board::create_begining_board();
    board.set_orientation('W');
    std::string expected =
        " |ABCDEFGH\n"
        "8|.B.B.B.B\n"
        "7|B.B.B.B.\n"
        "6|.B.B.B.B\n"
        "5|........\n"
        "4|........\n"
        "3|W.W.W.W.\n"
        "2|.W.W.W.W\n"
        "1|W.W.W.W.\n";

    std::string casted = static_cast<std::string>(board);

    assertEquals(casted, expected);
}

void BoardToString_BeginingHumanBlack_ReturnsString() {
    Board board = Board::create_begining_board();
    board.set_orientation('B');
    std::string expected =
        " |HGFEDCBA\n"
        "1|.W.W.W.W\n"
        "2|W.W.W.W.\n"
        "3|.W.W.W.W\n"
        "4|........\n"
        "5|........\n"
        "6|B.B.B.B.\n"
        "7|.B.B.B.B\n"
        "8|B.B.B.B.\n";

    std::string casted = static_cast<std::string>(board);

    assertEquals(casted, expected);
}

void BoardToString_HumanBlackKingInPosition_ReturnsString() {
    Board board = Board();
    board.set_orientation('B');
    Checker checker('B');
    checker.set_king();
    board.add_checker(Position::from_string("C5"), checker);
    std::string expected =
        " |HGFEDCBA\n"
        "1|........\n"
        "2|........\n"
        "3|........\n"
        "4|........\n"
        "5|.....Y..\n"
        "6|........\n"
        "7|........\n"
        "8|........\n";

    std::string casted = static_cast<std::string>(board);

    assertEquals(casted, expected);
}

void BoardToString_HumanBlackWhiteKingInPosition_ReturnsString() {
    Board board = Board();
    board.set_orientation('B');
    Checker checker('W');
    checker.set_king();
    board.add_checker(Position::from_string("C5"), checker);
    std::string expected =
        " |HGFEDCBA\n"
        "1|........\n"
        "2|........\n"
        "3|........\n"
        "4|........\n"
        "5|.....X..\n"
        "6|........\n"
        "7|........\n"
        "8|........\n";

    std::string casted = static_cast<std::string>(board);

    assertEquals(casted, expected);
}

void BoardGetState_AfterInit_ReturnsDefault() {
    Board board = Board();

    Board::State state = board.get_state();

    assertEquals(static_cast<int>(state),
                 static_cast<int>(Board::State::PLAYING));
}

void BoardProcessHumanCheckers_NoValues_NoResult(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    bool result = true;

    board.process_human_checkers(
        [&result](Position, const Checker &) { result = false; });

    assertTrue(result);
}

void BoardProcessHumanCheckers_OppositeValues_NoResult(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    bool result = true;
    Checker checker('W' + 'B' - human_side);
    board.add_checker(Position::from_string("C5"), checker);

    board.process_human_checkers(
        [&result](Position, const Checker &) { result = false; });

    assertTrue(result);
}

void BoardProcessHumanCheckers_ManyValues_ResultHuman(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    Checker first_opposite('W' + 'B' - human_side);
    Checker second_opposite('W' + 'B' - human_side);
    Checker third_opposite('W' + 'B' - human_side);
    Checker king_opposite('W' + 'B' - human_side);
    king_opposite.set_king();
    Checker first(human_side);
    Checker second(human_side);
    Checker third(human_side);
    Checker king(human_side);
    king.set_king();
    board.add_checker(Position::from_string("C5"), first_opposite);
    board.add_checker(Position::from_string("C8"), second_opposite);
    board.add_checker(Position::from_string("F5"), third_opposite);
    board.add_checker(Position::from_string("A1"), king_opposite);
    board.add_checker(Position::from_string("C7"), first);
    board.add_checker(Position::from_string("H6"), second);
    board.add_checker(Position::from_string("B2"), third);
    board.add_checker(Position::from_string("A8"), king);
    std::unordered_set<Position> positions;
    std::unordered_set<Position> expected_positions{
        Position::from_string("A8"), Position::from_string("B2"),
        Position::from_string("H6"), Position::from_string("C7")};

    board.process_human_checkers(
        [&positions](Position p, const Checker &) { positions.insert(p); });

    for (auto p : positions) {
        assertTrue(expected_positions.contains(p));
    }
    for (auto p : expected_positions) {
        assertTrue(positions.contains(p));
    }
}

void BoardProcessComputerCheckers_NoValues_NoResult(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    bool result = true;

    board.process_computer_checkers(
        [&result](Position, const Checker &) { result = false; });

    assertTrue(result);
}

void BoardProcessComputerCheckers_OppositeValues_NoResult(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    bool result = true;
    Checker checker(human_side);
    board.add_checker(Position::from_string("C5"), checker);

    board.process_computer_checkers(
        [&result](Position, const Checker &) { result = false; });

    assertTrue(result);
}

void BoardProcessComputerCheckers_TrueValues_ProcessResult(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    bool result = false;
    Checker checker('W' + 'B' - human_side);
    Position addable = Position::from_string("C5");
    board.add_checker(addable, checker);

    board.process_computer_checkers(
        [&result, addable](Position p, const Checker &) { result = (p == addable); });

    assertTrue(result);
}

void BoardHasHumanChecker_NoChecker_ReturnsFalse(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);

    bool result = board.has_human_checker(Position::from_string("A1"));

    assertFalse(result);
}

void BoardHasHumanChecker_OppositeChecker_ReturnsFalse(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    Position position = Position::from_string("A1");
    Checker checker('W' + 'B' - human_side);
    board.add_checker(position, checker);

    bool result = board.has_human_checker(position);
    
    assertFalse(result);
}

void BoardHasHumanChecker_HumanChecker_ReturnsTrue(char human_side) {
    Board board = Board();
    board.set_orientation(human_side);
    Position position = Position::from_string("A1");
    Checker checker(human_side);
    board.add_checker(position, checker);

    bool result = board.has_human_checker(position);
    
    assertTrue(result);
}
