#include "player.h"

#include <iostream>
#include <unordered_set>

#include "board.h"
#include "checker.h"
#include "position.h"

void HumanPlayer::move() {
    std::cout << static_cast<std::string>(board_) << std::endl;
    Positions checkers_necessary_to_move;
    Positions checkers_able_to_move;
    bool has_checkers = false;
    board_.process_human_checkers(
        [&checkers_able_to_move, &checkers_necessary_to_move, this, &has_checkers](
            Position position, const Checker &checker) {
            has_checkers = true;
            if (checker.is_king() &&
                    !board_.get_enemy_neighbors_of_king(position).empty() ||
                !checker.is_king() &&
                    !board_.get_enemy_neighbors(position).empty()) {
                checkers_necessary_to_move.insert(position);
            }
            if (checkers_necessary_to_move.empty()) {
                if (!board_.get_free_move(position).empty()) {
                    checkers_able_to_move.insert(position);
                }
            }
        });
    if (!has_checkers) {
        board_.set_state(Board::State::COMPUTER_WON);
        return;
    }
    if (checkers_necessary_to_move.empty() && checkers_able_to_move.empty()) {
        std::cout << "You can't move!" << std::endl;
        board_.set_state(Board::State::DRAW);
        return;
    }
    bool move_is_correct = false;
    while (!move_is_correct) {
        std::string current_position;
        std::string next_position;
        std::cout << "Your move: " << std::flush;
        std::cin >> current_position >> next_position;
        Position current = Position::from_string(current_position);
        Position next = Position::from_string(next_position);
        if (!current || !next ||
            !is_move_correct(Move(current, next), checkers_necessary_to_move,
                             checkers_able_to_move)) {
            std::cerr << "Error. Wrong move: " << current_position << " "
                      << next_position << " Try again!" << std::endl;
        } else {
            move_is_correct = true;
            board_.add_checker(next, board_.get_checker(current));
            board_.remove_checker(current);
        }
    }
}

void ConsolePlayer::move(Board &board) {
    if (board.is_computer_stagnation()) {
        return;
    }
}

bool HumanPlayer::is_move_correct(const Move &move,
                                  const Positions &necessary_to_move,
                                  const Positions &able_to_move) {
    if (!necessary_to_move.empty() && !necessary_to_move.contains(move.first)) {
        return false;
    }
    if (necessary_to_move.empty() && !able_to_move.contains(move.first)) {
        return false;
    }
    bool is_king = board_.get_checker(move.first).is_king();
    std::unordered_set<Position> eaten_checkers;
    for (auto direction : {Direction::DOWN_LEFT, Direction::DOWN_RIGHT,
                           Direction::UP_LEFT, Direction::UP_RIGHT}) {
        if (try_move(move.first, move.second, direction,
                     necessary_to_move.empty(), is_king, eaten_checkers)) {
            for (Position position : eaten_checkers) {
                board_.remove_checker(position);
            }
            return true;
        }
    }
    return false;
}

bool HumanPlayer::try_move(Position position, Position goal,
                           Direction direction, bool need_eat, bool is_king,
                           Positions eaten) const {
    bool found = false;
    apply_if_exists(
        position, direction,
        [&eaten, direction, goal, &found, this, is_king,
         need_eat](Position next) {
            if (board_.has_checker(next)) {
                if (board_.has_human_checker(next) || eaten.contains(next)) {
                    return;
                }
                eaten.insert(next);
                apply_if_exists(
                    next, direction,
                    [&eaten, goal, &found, this, is_king](Position real) {
                        if (real == goal) {
                            found = true;
                            return;
                        }
                        for (auto direction :
                             {Direction::DOWN_LEFT, Direction::DOWN_RIGHT,
                              Direction::UP_LEFT, Direction::UP_RIGHT}) {
                            if (try_move(real, goal, direction, true, is_king,
                                         eaten)) {
                                found = true;
                                return;
                            }
                        }
                    });
                if (!found) {
                    eaten.erase(next);
                }
            } else if (!need_eat) {
                if (next == goal) {
                    found = true;
                } else if (is_king) {
                    if (try_move(next, goal, direction, false, is_king,
                                 eaten)) {
                        found = true;
                    }
                }
            }
        });
    return found;
}
