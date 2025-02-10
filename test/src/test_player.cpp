#include "test_player.h"

#include <sstream>

#include "checker.h"
#include "player.h"
#include "position.h"
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

void HumanPlayerMove_SimpleEat_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("C3");
    Position enemy = Position::from_string("B2");
    board.add_checker(start, Checker('W'));
    board.add_checker(enemy, Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|..W.....\n"
        "2|.B......\n"
        "1|........\n"
        "Your move: ";
    in << "C3 A1\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("A1")));
    assertFalse(board.has_checker(start));
    assertFalse(board.has_checker(enemy));
}

void HumanPlayerMove_SimpleEatWrongMoving_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("C3");
    Position enemy = Position::from_string("B2");
    board.add_checker(start, Checker('W'));
    board.add_checker(enemy, Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|..W.....\n"
        "2|.B......\n"
        "1|........\n"
        "Your move: "
        "Your move: ";
    std::string expected_err = "Error. Wrong move: C3 D4 Try again!\n";
    in << "C3 D4\nC3 A1\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("A1")));
    assertFalse(board.has_checker(start));
    assertFalse(board.has_checker(enemy));
}

void HumanPlayerMove_MultipleEat_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    Position enemy_first = Position::from_string("B2");
    Position enemy_second = Position::from_string("D4");
    board.add_checker(start, Checker('W'));
    board.add_checker(enemy_first, Checker('B'));
    board.add_checker(enemy_second, Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|...B....\n"
        "3|........\n"
        "2|.B......\n"
        "1|W.......\n"
        "Your move: ";
    in << "A1 E5\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("E5")));
    assertFalse(board.has_checker(start));
    assertFalse(board.has_checker(enemy_first));
    assertFalse(board.has_checker(enemy_second));
}

void HumanPlayerMove_MultipleEatAndReturns_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("C1");
    Position enemy_first = Position::from_string("B2");
    Position enemy_second = Position::from_string("B4");
    Position enemy_third = Position::from_string("D2");
    Position enemy_fourth = Position::from_string("D4");
    board.add_checker(start, Checker('W'));
    board.add_checker(enemy_first, Checker('B'));
    board.add_checker(enemy_second, Checker('B'));
    board.add_checker(enemy_third, Checker('B'));
    board.add_checker(enemy_fourth, Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|.B.B....\n"
        "3|........\n"
        "2|.B.B....\n"
        "1|..W.....\n"
        "Your move: ";
    in << "C1 C1\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(start));
    assertFalse(board.has_checker(enemy_first));
    assertFalse(board.has_checker(enemy_second));
    assertFalse(board.has_checker(enemy_third));
    assertFalse(board.has_checker(enemy_fourth));
}

void HumanPlayerMove_MoveThrough_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("B2");
    Position fixed = Position::from_string("A1");
    board.add_checker(start, Checker('W'));
    board.add_checker(fixed, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|.W......\n"
        "1|W.......\n"
        "Your move: "
        "Your move: ";
    in << "A1 B2\nB2 C3\n";
    std::string expected_err = "Error. Wrong move: A1 B2 Try again!\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("C3")));
    assertFalse(board.has_checker(start));
    assertTrue(board.has_checker(fixed));
}

void HumanPlayerMove_BackMove_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("B2");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|.W......\n"
        "1|........\n"
        "Your move: "
        "Your move: ";
    in << "B2 A1\nB2 C3\n";
    std::string expected_err = "Error. Wrong move: B2 A1 Try again!\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("C3")));
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_Stop_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("B2");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|.W......\n"
        "1|........\n"
        "Your move: "
        "Your move: ";
    in << "B2 B2\nB2 C3\n";
    std::string expected_err = "Error. Wrong move: B2 B2 Try again!\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("C3")));
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_MoveBecameKing_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A7");
    Position finish = Position::from_string("B8");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|W.......\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|........\n"
        "Your move: ";
    in << "A7 B8\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(finish));
    assertTrue(board.get_checker(finish).is_king());
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_EatBecameKingSimple_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("B6");
    Position finish = Position::from_string("D8");
    Position enemy = Position::from_string("C7");
    board.add_checker(start, Checker('W'));
    board.add_checker(enemy, Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|..B.....\n"
        "6|.W......\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|........\n"
        "Your move: ";
    in << "B6 D8\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(finish));
    assertTrue(board.get_checker(finish).is_king());
    assertFalse(board.has_checker(start));
    assertFalse(board.has_checker(enemy));
}

void HumanPlayerMove_DoubleMoveKing_MoveConditions() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    Checker checker('W');
    checker.set_king();
    board.add_checker(start, checker);
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|X.......\n"
        "Your move: ";
    in << "A1 C3\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("C3")));
    assertFalse(board.has_checker(start));
}

void HumanPlayerMove_MoveBecameKing_ResetCounter() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A7");
    Position finish = Position::from_string("B8");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|W.......\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|........\n"
        "Your move: ";
    in << "A7 B8\n";
    board.increment_stagnation_counter();
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(board.get_stagnation_counter(), 0);
}

void HumanPlayerMove_MoveBecameKing_SetHumanHasKing() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A7");
    Position finish = Position::from_string("B8");
    board.add_checker(start, Checker('W'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|W.......\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|........\n"
        "Your move: ";
    in << "A7 B8\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertTrue(board.has_human_king());
}

void HumanPlayerMove_SimpleEat_ResetCounter() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("C3");
    Position enemy = Position::from_string("B2");
    board.add_checker(start, Checker('W'));
    board.add_checker(enemy, Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|..W.....\n"
        "2|.B......\n"
        "1|........\n"
        "Your move: ";
    in << "C3 A1\n";
    board.increment_stagnation_counter();
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertEquals(board.get_stagnation_counter(), 0);
}

void HumanPlayerMove_SimpleEat_ResetComputerHasKing() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("C3");
    Position enemy = Position::from_string("B2");
    board.add_checker(start, Checker('W'));
    board.add_checker(enemy, Checker('B'));
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|........\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|..W.....\n"
        "2|.B......\n"
        "1|........\n"
        "Your move: ";
    in << "C3 A1\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertFalse(board.has_computer_king());
}

void HumanPlayerMove_UselessMove_IncrementCounter() {
    Board board;
    board.set_orientation('W');
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;
    Position start = Position::from_string("A1");
    Position enemy = Position::from_string("A7");
    Checker human('W');
    human.set_king();
    Checker computer('B');
    computer.set_king();
    board.add_checker(start, human);
    board.add_checker(enemy, computer);
    HumanPlayer player(board, out, err, in);
    std::string expected_out = " |ABCDEFGH\n"
        "8|........\n"
        "7|Y.......\n"
        "6|........\n"
        "5|........\n"
        "4|........\n"
        "3|........\n"
        "2|........\n"
        "1|X.......\n"
        "Your move: ";
    in << "A1 B2\n";
    board.set_has_computer_king(true);
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), "");
    assertEquals(board.get_stagnation_counter(), 1);
}

void HumanPlayerMove_WrongInput_ErrorMessage() {
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
    in << "AB5 D4\nA1 B2\n";
    std::string expected_err = "Error. Wrong move: AB5 D4 Try again!\n";
    
    player.move();

    assertEquals(out.str(), expected_out);
    assertEquals(err.str(), expected_err);
    assertEquals(static_cast<int>(board.get_state()), static_cast<int>(Board::State::PLAYING));
    assertTrue(board.has_checker(Position::from_string("B2")));
    assertFalse(board.has_checker(start));
}
