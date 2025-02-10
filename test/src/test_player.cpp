#include "test_player.h"

#include <sstream>

#include "checker.h"
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

void HumanPlayerMove_CannotMove_DrawConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    board.add_checker(Position::from_string("A1"), Checker('W'));
    board.add_checker(Position::from_string("B2"), Checker('B'));
    board.add_checker(Position::from_string("C3"), Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|..B.....\n"
        "2|.B......\n"
        "1|W.......\n"
        "You can't move!\n";

    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::DRAW));
}

void HumanPlayerMove_UselessMoves_DrawConditions() {
    Board board;
    board.set_orientation('W');
    for (int i = 0; i < 15; ++i) {
        board.increment_stagnation_counter();
    }
    board.set_has_computer_king(true);
    board.set_has_human_king(true);
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Checker human('W');
    human.set_king();
    Checker computer('B');
    computer.set_king();
    board.add_checker(Position::from_string("A1"), human);
    board.add_checker(Position::from_string("A7"), computer);
    HumanPlayer player(board, out, err, in);
    
    player.move();

    assertEquals(out.str(), "");
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::DRAW));
}

void HumanPlayerMove_SimpleMove_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|W.......\n"
        "Your move: ";
    in << "A1 B2\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("B2")));
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_SimpleMoveAnotherFormat_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|W.......\n"
        "Your move: ";
    in << "A1  B2\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("B2")));
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_StraightMove_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|W.......\n"
        "Your move: "
        "Your move: ";
    in << "A1 A6\nA1 B2\n";
    std::string expected_err = "Error. Wrong move: A1 A6 Try again!\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("B2")));
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_DoubleMove_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|W.......\n"
        "Your move: "
        "Your move: ";
    in << "A1 C3\nA1 B2\n";
    std::string expected_err = "Error. Wrong move: A1 C3 Try again!\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("B2")));
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_MoveGhost_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|W.......\n"
        "Your move: "
        "Your move: ";
    in << "C1 B2\nA1 B2\n";
    std::string expected_err = "Error. Wrong move: C1 B2 Try again!\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("B2")));
    assertFalse(board.has_checker(start));
}
