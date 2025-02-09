#include <position.h>

#include <iostream>  //
#include <stdexcept>

Position Position::from_string(const std::string &position) noexcept {
    if (position.size() != 2) {
        return Position('\0', '\0');
    }
    return Position(position[0], position[1]);
}

bool Position::operator==(const Position &other) const {
    return column == other.column && row == other.row;
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}

Position::operator bool() const {
    return column <= 'H' && column >= 'A' && row >= '1' && row <= '8';
}

Move::operator Direction() const {
    if (second.column > first.column && second.row < first.row) {
        return Direction::DOWN_RIGHT;
    }
    if (second.column < first.column && second.row < first.row) {
        return Direction::DOWN_LEFT;
    }
    if (second.column > first.column && second.row > first.row) {
        return Direction::UP_RIGHT;
    }
    if (second.column < first.column && second.row > first.row) {
        return Direction::UP_LEFT;
    }
    throw std::logic_error("Error. Some coordinates are equal!");
}

Position operator+(Position position, Direction direction) {
    switch (direction) {
    case Direction::DOWN_RIGHT:
        if (position.column == 'H' || position.row == '1')
            throw std::logic_error("Error. Can't move DOWN_RIGHT!");
        return Position(position.column + 1, position.row - 1);

    case Direction::UP_RIGHT:
        if (position.column == 'H' || position.row == '8')
            throw std::logic_error("Error. Can't move UP_RIGHT!");
        return Position(position.column + 1, position.row + 1);

    case Direction::DOWN_LEFT:
        if (position.column == 'A' || position.row == '1')
            throw std::logic_error("Error. Can't move DOWN_LEFT!");
        return Position(position.column - 1, position.row - 1);

    case Direction::UP_LEFT:
        if (position.column == 'A' || position.row == '8')
            throw std::logic_error("Error. Can't move UP_LEFT!");
        return Position(position.column - 1, position.row + 1);

    default:
        throw std::logic_error("Error. Unexpected direction!");
    }
}

bool apply_if_exists(Position position, Direction direction, Operation o) {
    if (exists(position, direction)) {
        o(position + direction);
        return true;
    }
    return false;
}

bool exists(Position position,
            Direction direction) {  // TODO: move to class definition
    switch (direction) {
    case Direction::UP_LEFT:
        if (position.column == 'A' || position.row == '8') {
            return false;
        }
        break;

    case Direction::UP_RIGHT:
        if (position.column == 'H' || position.row == '8') {
            return false;
        }
        break;

    case Direction::DOWN_LEFT:
        if (position.column == 'A' || position.row == '1') {
            return false;
        }
        break;

    case Direction::DOWN_RIGHT:
        if (position.column == 'H' || position.row == '1') {
            return false;
        }
        break;

    default:
        throw std::logic_error("Error. Unexpected direction!");
    }
    return true;
}
