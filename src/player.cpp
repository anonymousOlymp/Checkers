#include "player.h"

#include <iostream>
#include <random>
#include <unordered_set>

#include "board.h"
#include "checker.h"
#include "position.h"

void HumanPlayer::move() {
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
                    !board_.get_king_eat_moves(position, true).empty() ||
                !checker.is_king() && !board_.get_eat_moves(position, true).empty()) {
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
    out_ << static_cast<std::string>(board_) << std::flush;
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
            !try_do_move(Move(current, next), checkers_necessary_to_move,
                             checkers_able_to_move)) {
            err_ << "Error. Wrong move: " << current_position << " "
                      << next_position << " Try again!" << std::endl;
        } else {
            move_is_correct = true;
        }
    }
}

bool HumanPlayer::try_do_move(const Move &move, const Positions &necessary_to_move,
                                  const Positions &able_to_move) {
    if (!necessary_to_move.empty() && !necessary_to_move.contains(move.first)) {
        return false;
    }
    if (necessary_to_move.empty() && !able_to_move.contains(move.first)) {
        return false;
    }
    Checker moved = board_.get_checker(move.first);
    board_.remove_checker(move.first);
    bool is_king = moved.is_king();
    if (!necessary_to_move.empty()) {
        Moves appropriate_to_eat;
        if (is_king) {
            appropriate_to_eat = board_.get_king_eat_moves(move.first, true);
        } else {
            appropriate_to_eat = board_.get_eat_moves(move.first, true);
        }
        std::unordered_set<Position> eaten_checkers;
        for (Move eaten : appropriate_to_eat) {
            auto result = try_eat(eaten, move.second, is_king, eaten_checkers);
            if (result == MoveResult::SUCCESS_KING) {
                moved.set_king();
                board_.set_has_human_king(true);
            }
            if (result != MoveResult::FAIL) {
                board_.reset_stagnation_counter();
                board_.set_has_computer_king(false);
                for (Position position : eaten_checkers) {
                    board_.remove_checker(position);
                }
                board_.add_checker(move.second, moved);
                return true;
            }
        }
        board_.add_checker(move.first, moved);
        return false;
    }
    Moves appropriate_to_go;
    if (is_king) {
        appropriate_to_go = board_.get_king_free_moves(move.first);
    } else {
        appropriate_to_go = board_.get_free_moves(move.first, true);
    }
    for (Move simple_move : appropriate_to_go) {
        if (simple_move.second == move.second) {
            bool became_king = !is_king && board_.is_changed_to_king(move.second, true);
            if (became_king) {
                moved.set_king();
                board_.set_has_human_king(true);
                board_.reset_stagnation_counter();
            } else if (board_.has_human_king() && board_.has_computer_king()) {
                board_.increment_stagnation_counter();
            }
            board_.add_checker(move.second, moved);
            return true;
        }
    }
    board_.add_checker(move.first, moved);
    return false;
}

HumanPlayer::MoveResult HumanPlayer::try_eat(Move move, Position goal, bool is_king, Positions &eaten) {
    Direction direction = move;
    Position current = move.second;
    eaten.insert(current);
    while (exists(current, direction)) {
        Position next = current + direction;
        is_king = board_.is_changed_to_king(next, true);
        Moves appropriate_to_eat;
        if (is_king) {
            appropriate_to_eat = board_.get_king_eat_moves(next, true);
        } else {
            appropriate_to_eat = board_.get_eat_moves(next, true);
        }
        bool can_eat = false;
        for (Move eat_goal : appropriate_to_eat) {
            if (!eaten.contains(eat_goal.second)) {
                can_eat = true;
                MoveResult result = try_eat(eat_goal, goal, is_king, eaten);
                if (result != MoveResult::FAIL) {
                    return result;
                }
            }
        }
        if (!can_eat) {
            if (goal == next) {
                if (is_king) {
                    return MoveResult::SUCCESS_KING;
                }
                return MoveResult::SUCCESS_SIMPLE;
            }
        }
        if (!is_king) {
            break;
        }
        current = next;
    }
    eaten.insert(move.second);
    return MoveResult::FAIL;
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
                     !necessary_to_move.empty(), is_king, eaten_checkers)) {
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
    board_.add_checker(move.first, moved);
    return false;
}

bool HumanPlayer::try_move(Position position, Position goal,
                           Direction direction, bool need_eat, bool &is_king,
                           Positions &eaten) const {
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
                    eaten_moves = board_.get_king_eat_moves(real, true);
                } else {
                    eaten_moves = board_.get_eat_moves(real, true);
                }
                Moves tmp_eaten_moves;
                for (Move eaten_move : eaten_moves) {
                    if (!eaten.contains(eaten_move.second)) {
                        tmp_eaten_moves.push_back(eaten_move);
                    }
                }
                tmp_eaten_moves.swap(eaten_moves);
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
    if (need_eat) {
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
            neighbors_can_eat = board_.get_king_eat_moves(position, false);
        } else {
            neighbors_can_eat = board_.get_eat_moves(position, false);
        }
        necessary_to_move.insert(necessary_to_move.end(),
                                 neighbors_can_eat.begin(),
                                 neighbors_can_eat.end());
        if (necessary_to_move.empty()) {
            Moves free = (checker.is_king()) ? board_.get_king_free_moves(position) : board_.get_free_moves(position, false);
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
            eat_positions = board_.get_king_eat_moves(next, true);
        } else {
            eat_positions = board_.get_eat_moves(next, true);
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
