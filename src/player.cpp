#include "player.h"

#include <iostream>

#include "checker.h"
#include "position.h"

void HumanPlayer::move(Board &board) {
    std::cout << static_cast<std::string>(board) << std::endl;
    std::vector<Position> checkers_necessary_to_move;
    std::vector<Position> checkers_able_to_move;
    board.process_human_checkers(
        [&checkers_able_to_move, &checkers_necessary_to_move, &board](
            Position position, const Checker &checker) {
            if (checker.is_king() &&
                    !board.get_enemy_neighbors_of_king(position).empty() ||
                !checker.is_king() &&
                    !board.get_enemy_neighbors(position).empty()) {
                checkers_necessary_to_move.push_back(position);
            }
            if (checkers_necessary_to_move.empty()) {
                if (!board.get_free_move(position).empty()) {
                    checkers_able_to_move.push_back(position);
                }
            }
        });
    bool move_is_correct = false;
    while (!move_is_correct) {
        std::string current_position;
        std::string next_position;
        std::cout << "Your move: " << std::flush;
        std::cin >> current_position >> next_position;
        if (!is_move_correct(current_position, next_position, checkers_necessary_to_move, checkers_able_to_move)) {
            std::cerr << "Error. Wrong move: " << current_position << " "
                      << next_position << " Try again!" << std::endl;
        } else {
            move_is_correct = true;
        }
    }
}

void ConsolePlayer::move(Board &board) {
    if (board.is_computer_stagnation()) {
        return;
    }
}

bool HumanPlayer::is_move_correct(const std::string &current_position, const std::string &next_position) {
    if (current_position.size() != 2 || next_position.size() != 2) {
        return false;
    }
    return true;
}
