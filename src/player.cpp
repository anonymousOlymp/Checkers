#include "player.h"

#include <iostream>

const std::string HumanPlayer::get_name() const noexcept {
    return "You";
}

bool HumanPlayer::is_won() const {
    
}

void HumanPlayer::move(Board &board) {
    if (board.is_human_stagnation()) {
        return;
    }
    std::cout << static_cast<std::string>(board) << std::endl;
    bool move_is_correct = false;
    while (!move_is_correct) {
        std::string current_position;
        std::string next_position;
        std::cout << "Your move: " << std::flush;
        std::cin >> current_position >> next_position;
        if (current_position.size() != 2
            || next_position.size() != 2
            || !(board.try_move_human(
                current_position[0],
                current_position[1],
                next_position[0],
                next_position[1]))) {
            std::cerr << "Error. Wrong move: " << current_position
                << " " << next_position
                << " Try again!" << std::endl;
        } else {
            move_is_correct = true;
        }
    }
}

const std::string ConsolePlayer::get_name() const noexcept {
    return "Computer";
}

bool ConsolePlayer::is_won() const {
    
}

void ConsolePlayer::move(Board &board) {
    if (board.is_computer_stagnation()) {
        return;
    }
    
}
