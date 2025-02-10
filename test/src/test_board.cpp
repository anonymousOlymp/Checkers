#include "test_board.h"

#include "board.h"
#include "test.h"

void BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere(const std::string &position, bool expected, char type) {
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
    std::string expected = " |ABCDEFGH\n"\
                           "8|.B.B.B.B\n"\
                           "7|B.B.B.B.\n"\
                           "6|.B.B.B.B\n"\
                           "5|........\n"\
                           "4|........\n"\
                           "3|W.W.W.W.\n"\
                           "2|.W.W.W.W\n"\
                           "1|W.W.W.W.\n";

    std::string casted = static_cast<std::string>(board);

    assertEquals(casted, expected);
}

void BoardToString_BeginingHumanBlack_ReturnsString() {
    Board board = Board::create_begining_board();
    board.set_orientation('B');
    std::string expected = " |HGFEDCBA\n"\
                           "1|.W.W.W.W\n"\
                           "2|W.W.W.W.\n"\
                           "3|.W.W.W.W\n"\
                           "4|........\n"\
                           "5|........\n"\
                           "6|B.B.B.B.\n"\
                           "7|.B.B.B.B\n"\
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
    std::string expected = " |HGFEDCBA\n"\
                           "1|........\n"\
                           "2|........\n"\
                           "3|........\n"\
                           "4|........\n"\
                           "5|.....Y..\n"\
                           "6|........\n"\
                           "7|........\n"\
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
    std::string expected = " |HGFEDCBA\n"\
                           "1|........\n"\
                           "2|........\n"\
                           "3|........\n"\
                           "4|........\n"\
                           "5|.....X..\n"\
                           "6|........\n"\
                           "7|........\n"\
                           "8|........\n";

    std::string casted = static_cast<std::string>(board);

    assertEquals(casted, expected);
}

void BoardGetState_AfterInit_ReturnsDefault() {
    Board board = Board();
    
    Board::State state = board.get_state();

    assertEquals(static_cast<int>(state), static_cast<int>(Board::State::PLAYING));
}
