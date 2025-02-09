#include "board.h"

#include <sstream>

#include "checker.h"
#include "position.h"

Board::Board() {
    for (char column = 'A'; column <= 'H'; column += 2) {
        board_.emplace(Position(column, '1'), Checker('W'));
        board_.emplace(Position(column, '3'), Checker('W'));
        board_.emplace(Position(column, '7'), Checker('B'));
    }
    for (char column = 'B'; column <= 'H'; column += 2) {
        board_.emplace(Position(column, '2'), Checker('W'));
        board_.emplace(Position(column, '6'), Checker('B'));
        board_.emplace(Position(column, '8'), Checker('B'));
    }
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
        result << " |HGFEDCBA\n" << std::endl;
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

void Board::process_checkers(const Functor &functor) const {
    for (const auto &position_to_checker : board_) {
        functor(position_to_checker.first, position_to_checker.second);
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
    for (auto direction : {Direction::DOWN_LEFT, Direction::DOWN_RIGHT,
                           Direction::UP_LEFT, Direction::UP_RIGHT}) {
        apply_if_exists(position, direction,
                        [&result, this, position](Position next) {
                            if (!has_checker(next)) {
                                result.emplace_back(position, next);
                            }
                        });
    }
    return result;
}

Moves Board::get_eat_moves(Position position) const {
    std::vector<Position> result;
    char current_side = get_checker(position).get_side();
    for (auto direction : {Direction::DOWN_LEFT, Direction::DOWN_RIGHT,
                           Direction::UP_LEFT, Direction::UP_RIGHT}) {
        apply_if_exists(position, direction,
                        [&result, this, position, current_side](Position next) {
                            if (has_checker(next) &&
                                get_checker(next).get_side() != current_side) {
                                result.push_back(next);
                            }
                        });
    }
    return result;
}

Moves Board::get_king_eat_moves(
    Position position) const {
    std::vector<Position> result = get_neighbors_positions(position);
    char current_side = get_checker(position).get_side();
    std::vector<Position> buffer;
    for (Position next : result) {
        Direction direction = Move(position, next);
        bool terminate = false;
        while (apply_if_exists(
                   next, direction,
                   [&buffer, this, current_side, &terminate](Position p) {
                       if (has_checker(p) &&
                           get_checker(p).get_side() != current_side) {
                           buffer.push_back(p);
                           terminate = true;
                       }
                   }) &&
               !terminate);
    }
    return buffer;
}

std::vector<Position> Board::get_neighbors_positions(Position position) {
    std::vector<Position> result;
    for (auto direction : {Direction::DOWN_LEFT, Direction::DOWN_RIGHT,
                           Direction::UP_LEFT, Direction::UP_RIGHT}) {
        apply_if_exists(position, direction,
                        [&result, position](Position next) {
                            result.push_back(next);
                        });
    }
    return result;
}

char Board::position_to_char(Position position) const {
    if (has_checker(position)) {
        return static_cast<char>(get_checker(position));
    }
    return '.';
}
