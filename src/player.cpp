#include "player.h"

#include <iostream>
#include <random>
#include <unordered_set>

#include "board.h"
#include "checker.h"
#include "position.h"

void HumanPlayer::move() {
    out_ << static_cast<std::string>(board_) << std::endl;
    Positions checkers_necessary_to_move;
    Positions checkers_able_to_move;
    bool has_checkers = false;
    board_.process_human_checkers(
        [&checkers_able_to_move, &checkers_necessary_to_move, this,
         &has_checkers](Position position, const Checker &checker) {
            has_checkers = true;
            if (checker.is_king()) {
                board_.set_has_human_king(true);
            }
            if (checker.is_king() &&
                    !board_.get_king_eat_moves(position).empty() ||
                !checker.is_king() && !board_.get_eat_moves(position).empty()) {
                checkers_necessary_to_move.insert(position);
            }
            if (checkers_necessary_to_move.empty()) {
                if (!board_.get_free_moves(position).empty()) {
                    checkers_able_to_move.insert(position);
                }
            }
        });
    if (!has_checkers) {
        board_.set_state(Board::State::COMPUTER_WON);
        return;
    }
    if (board_.has_human_king() && board_.has_computer_king() &&
        board_.get_stagnation_counter() == 15) {
        board_.set_state(Board::State::DRAW);
        return;
    }
    if (checkers_necessary_to_move.empty() && checkers_able_to_move.empty()) {
        out_ << "You can't move!" << std::endl;
        board_.set_state(Board::State::DRAW);
        return;
    }
    bool move_is_correct = false;
    while (!move_is_correct) {
        std::string current_position;
        std::string next_position;
        out_ << "Your move: " << std::flush;
        in_ >> current_position >> next_position;
        Position current = Position::from_string(current_position);
        Position next = Position::from_string(next_position);
        bool was_king_produced = false;
        if (!current || !next ||
            !is_move_correct(Move(current, next), checkers_necessary_to_move,
                             checkers_able_to_move, was_king_produced)) {
            err_ << "Error. Wrong move: " << current_position << " "
                      << next_position << " Try again!" << std::endl;
        } else {
            move_is_correct = true;
            Checker moved = board_.get_checker(current);
            if (board_.has_human_king() && board_.has_computer_king()) {
                board_.increment_stagnation_counter();
            }
            if (was_king_produced) {
                board_.set_has_human_king(true);
                board_.reset_stagnation_counter();
            }
        }
    }
}

bool HumanPlayer::is_move_correct(const Move &move,
                                  const Positions &necessary_to_move,
                                  const Positions &able_to_move,
                                  bool &was_king_produced) {
    if (!necessary_to_move.empty() && !necessary_to_move.contains(move.first)) {
        return false;
    }
    if (necessary_to_move.empty() && !able_to_move.contains(move.first)) {
        return false;
    }
    Checker moved = board_.get_checker(move.first);
    board_.remove_checker(move.first);
    bool is_king = moved.is_king();
    bool was_king = is_king;
    std::unordered_set<Position> eaten_checkers;
    for (auto direction : {Direction::DOWN_LEFT, Direction::DOWN_RIGHT,
                           Direction::UP_LEFT, Direction::UP_RIGHT}) {
        if (try_move(move.first, move.second, direction,
                     necessary_to_move.empty(), is_king, eaten_checkers)) {
            if (!eaten_checkers.empty()) {
                board_.reset_stagnation_counter();
                board_.set_has_computer_king(false);
            }
            for (Position position : eaten_checkers) {
                board_.remove_checker(position);
            }
            if (is_king) {
                moved.set_king();
            }
            board_.add_checker(move.second, moved);
            was_king_produced = is_king && !was_king;
            return true;
        }
    }
    return false;
}

bool HumanPlayer::try_move(Position position, Position goal,
                           Direction direction, bool need_eat, bool &is_king,
                           Positions eaten) const {
    if (!exists(position, direction)) {
        return false;
    }
    Position next = position + direction;
    if (board_.has_checker(next)) {
        if (board_.has_human_checker(next) || eaten.contains(next)) {
            return false;
        }
        eaten.insert(next);
        if (exists(next, direction)) {
            Position real = next + direction;
            while (!board_.has_checker(real)) {
                bool real_is_king = board_.is_changed_to_king(next, true);
                Moves eaten_moves;
                if (real_is_king) {
                    eaten_moves = board_.get_king_eat_moves(real);
                } else {
                    eaten_moves = board_.get_eat_moves(real);
                }
                for (Move eaten_move : eaten_moves) {
                    bool deep_is_king = real_is_king;
                    if (try_move(eaten_move.second, goal, eaten_move, true, deep_is_king, eaten)) {
                        is_king = deep_is_king;
                        return true;
                    }
                }
                if (eaten_moves.empty() && real == goal) {
                    is_king = real_is_king;
                    return true;
                }
                if (!is_king || !exists(real, direction)) {
                    break;
                }
                real = real + direction;
            }
        }
        eaten.erase(next);
        return false;
    }
    while (!board_.has_checker(next)) {
        bool next_is_king = board_.is_changed_to_king(next, true);
        if (next == goal) {
            is_king = next_is_king;
            return true;
        }
        if (!is_king || !exists(next, direction)) {
            break;
        }
        next = next + direction;
    }
    return false;
}

void ComputerPlayer::move() {
    Moves necessary_to_move;
    Moves able_to_move;
    bool has_checkers = false;
    board_.process_computer_checkers([&able_to_move, &necessary_to_move, this,
                                      &has_checkers](Position position,
                                                     const Checker &checker) {
        has_checkers = true;
        Moves neighbors_can_eat;
        if (checker.is_king()) {
            board_.set_has_computer_king(true);
            neighbors_can_eat = board_.get_king_eat_moves(position);
        } else {
            neighbors_can_eat = board_.get_eat_moves(position);
        }
        necessary_to_move.insert(necessary_to_move.end(),
                                 neighbors_can_eat.begin(),
                                 neighbors_can_eat.end());
        if (necessary_to_move.empty()) {
            Moves free = board_.get_free_moves(position);
            able_to_move.insert(able_to_move.end(), free.begin(), free.end());
        }
    });
    if (!has_checkers) {
        board_.set_state(Board::State::HUMAN_WON);
        return;
    }
    if (board_.has_human_king() && board_.has_computer_king() &&
        board_.get_stagnation_counter() == 15) {
        board_.set_state(Board::State::DRAW);
        return;
    }
    if (necessary_to_move.empty() && able_to_move.empty()) {
        out_ << "Computer can't move!" << std::endl;
        board_.set_state(Board::State::DRAW);
        return;
    }
    Moves moves =
        (necessary_to_move.empty()) ? able_to_move : necessary_to_move;
    std::uniform_int_distribution<> distribution(0, moves.size() - 1);
    Move chosen_move = moves[distribution(mt_)];
    Direction direction = chosen_move;
    std::unordered_set<Position> eaten;
    Checker moved = board_.get_checker(chosen_move.first);
    board_.remove_checker(chosen_move.first);
    bool is_king = moved.is_king();
    bool was_king = is_king;
    eat_all(chosen_move, direction, eaten, is_king);
    if (!eaten.empty()) {
        board_.reset_stagnation_counter();
        board_.set_has_computer_king(false);
    }
    for (Position position : eaten) {
        board_.remove_checker(position);
    }
    Position next = chosen_move.second;
    if (board_.has_computer_king() && board_.has_human_king()) {
        board_.increment_stagnation_counter();
    }
    if (!was_king && is_king) {
        board_.set_has_computer_king(true);
        board_.reset_stagnation_counter();
        moved.set_king();
    }
    board_.add_checker(next, moved);
}

void ComputerPlayer::eat_all(Move &chosen, Direction &direction,
                             Positions &eaten, bool &is_king) {
    while (board_.has_checker(chosen.second)) {
        Position next = chosen.second + direction;
        eaten.insert(chosen.second);
        chosen = Move(chosen.first, next);
        is_king = board_.is_changed_to_king(next, false);
        Moves eat_positions;
        if (is_king) {
            eat_positions = board_.get_king_eat_moves(next);
        } else {
            eat_positions = board_.get_eat_moves(next);
        }
        for (Move eat_move : eat_positions) {
            if (!eaten.contains(eat_move.second)) {
                chosen = Move(chosen.first, eat_move.second);
                direction = eat_move;
                break;
            }
        }
    }
}
