#include "test_player.h"

#include <sstream>

#include "player.h"
#include "test.h"

void HumanPlayerMove_EmptyBoard_ComputerWinConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    HumanPlayer player(board, out, err, in);

    player.move();

    assertEquals(out.str(), "");
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::COMPUTER_WON));
}
