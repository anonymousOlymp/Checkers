#include "board.h"

#include <sstream>

#include "checker.h"
#include "position.h"

Board Board::create_begining_board() {
    Board board;
    for (char column = 'A'; column <= 'H'; column += 2) {
        board.board_.emplace(Position(column, '1'), Checker('W'));
        board.board_.emplace(Position(column, '3'), Checker('W'));
        board.board_.emplace(Position(column, '7'), Checker('B'));
    }
    for (char column = 'B'; column <= 'H'; column += 2) {
        board.board_.emplace(Position(column, '2'), Checker('W'));
        board.board_.emplace(Position(column, '6'), Checker('B'));
        board.board_.emplace(Position(column, '8'), Checker('B'));
    }
    return board;
}

Board::operator std::string() const {
    std::stringstream result;
    if (side_ == 'W') {
        result << " |ABCDEFGH" << std::endl;
        for (char row = '8'; row >= '1'; --row) {
            result << row << '|';
            for (char column = 'A'; column <= 'H'; ++column) {
                result << position_to_char(Position(column, row));
            }
            result << std::endl;
        }
    } else {
        result << " |HGFEDCBA" << std::endl;
        for (char row = '1'; row <= '8'; ++row) {
            result << row << '|';
            for (char column = 'H'; column >= 'A'; --column) {
                result << position_to_char(Position(column, row));
            }
            result << std::endl;
        }
    }
    return result.str();
}

Board::State Board::get_state() const noexcept { return state_; }

void Board::set_state(State state) noexcept { state_ = state; }

void Board::set_orientation(char orientation) noexcept { side_ = orientation; }

void Board::process_human_checkers(const Functor &functor) const {
    for (const auto &position_to_checker : board_) {
        if (position_to_checker.second.get_side() == side_) {
            functor(position_to_checker.first, position_to_checker.second);
        }
    }
}

void Board::process_computer_checkers(const Functor &functor) const {
    for (const auto &position_to_checker : board_) {
        if (position_to_checker.second.get_side() != side_) {
            functor(position_to_checker.first, position_to_checker.second);
        }
    }
}

bool Board::has_computer_checker(Position position) const {
    return has_checker(position) && get_checker(position).get_side() != side_;
}

bool Board::has_human_checker(Position position) const {
    return has_checker(position) && get_checker(position).get_side() == side_;
}

bool Board::has_checker(Position position) const {
    return board_.contains(position);
}

void Board::remove_checker(Position position) { board_.erase(position); }

void Board::add_checker(Position position, Checker checker) {
    board_.emplace(position, checker);
}

const Checker &Board::get_checker(Position position) const {
    return board_.find(position)->second;
}

Moves Board::get_free_moves(Position position) const {
    std::vector<Move> result;
    for (auto direction : get_all_direction_values()) {
        if (exists(position, direction)) {
            Position next = position + direction;
            if (!has_checker(next)) {
                result.emplace_back(position, next);
            }
        }
    }
    return result;
}

Moves Board::get_eat_moves(Position position, bool is_human) const {
    std::vector<Move> result;
    char current_side = (is_human) ? side_ : ('W' + 'H' - side_);
    for (auto direction : get_all_direction_values()) {
        if (exists(position, direction)) {
            Position next = position + direction;
            if (has_checker(next) &&
                get_checker(next).get_side() != current_side) {
                if (exists(next, direction)) {
                    Position continuation = next + direction;
                    if (!has_checker(continuation)) {
                        result.push_back(Move(position, next));
                    }
                }
            }
        }
    }
    return result;
}

Moves Board::get_king_eat_moves(Position position, bool is_human) const {
    std::vector<Move> result;
    char current_side = (is_human) ? side_ : ('W' + 'H' - side_);
    for (auto direction : get_all_direction_values()) {
        Position current = position;
        while (exists(current, direction)) {
            Position next = current + direction;
            if (has_checker(next)) {
                if (get_checker(next).get_side() != current_side &&
                    exists(next, direction)) {
                    Position continuation = next + direction;
                    if (!has_checker(continuation)) {
                        result.push_back(Move(position, next));
                    }
                }
                break;
            }
            current = next;
        }
    }
    return result;
}

char Board::get_side() const { return side_; }

bool Board::has_human_king() const { return has_human_king_; }

void Board::set_has_human_king(bool has_human_king) {
    has_human_king_ = has_human_king;
}

bool Board::has_computer_king() const { return has_computer_king_; }

void Board::set_has_computer_king(bool has_computer_king) {
    has_computer_king_ = has_computer_king;
}

int Board::get_stagnation_counter() const { return stagnation_counter_; }

void Board::increment_stagnation_counter() { ++stagnation_counter_; }

void Board::reset_stagnation_counter() { stagnation_counter_ = 0; }

bool Board::is_changed_to_king(Position position, bool is_human) const {
    if (position.row == '1' && (is_human ^ (side_ == 'W')) ||
        position.row == '8' && (is_human ^ (side_ == 'B'))) {
        return true;
    }
    return false;
}

char Board::position_to_char(Position position) const {
    if (has_checker(position)) {
        return static_cast<char>(get_checker(position));
    }
    return '.';
}
