#include "test_board.h"

#include "board.h"
#include "test.h"

void CreateBeginingBoard_VariousPosition_ReturnsIsThere(std::string position, bool expected, char type) {
    Position p = Position::from_string(position);

    Board board = Board::create_begining_board();

    assertEquals(board.has_checker(p), expected);
    if (expected) {
        assertEquals(board.get_checker(p), type);
    }
}
