#include <position.h>

#include <stdexcept>

bool Position::operator==(const Position &other) const {
    return column == other.column
        && row == other.row;
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}

Move::operator Direction() const {
    return second - first;
}

Position operator+(Position position, Direction direction) {
    switch (direction) {
        case Direction::UP_LEFT:
            if (position.column == '1' || position.row == 'H')
                throw std::logic_error("Error. Can't move UP_LEFT!");
            return Position(position.column - 1, position.row + 1);
        
        case Direction::UP_RIGHT:
            if (position.column == '8' || position.row == 'H')
                throw std::logic_error("Error. Can't move UP_RIGHT!");
            return Position(position.column + 1, position.row + 1);

        case Direction::DOWN_LEFT:
            if (position.column == '1' || position.row == 'A')
                throw std::logic_error("Error. Can't move DOWN_LEFT!");
            return Position(position.column - 1, position.row - 1);
        
        case Direction::DOWN_RIGHT:
            if (position.column == '8' || position.row == 'A')
                throw std::logic_error("Error. Can't move DOWN_RIGHT!");
            return Position(position.column + 1, position.row - 1);
        
        default:
            throw std::logic_error("Error. Unexpected direction!");
    }
}

Position operator-(Position position, Direction direction) {
    switch (direction) {
        case Direction::UP_LEFT:
            return position + Direction::DOWN_RIGHT;
        
        case Direction::UP_RIGHT:
            return position + Direction::DOWN_LEFT;

        case Direction::DOWN_LEFT:
            return position + Direction::UP_RIGHT;
        
        case Direction::DOWN_RIGHT:
            return position + Direction::UP_LEFT;
        
        default:
            throw std::logic_error("Error. Unexpected direction!");
    }
}

Direction operator-(Position first, Position second) {
    if (first.column > second.column && first.row < second.row) {
        return Direction::UP_LEFT;
    }
    if (first.column < second.column && first.row < second.row) {
        return Direction::UP_RIGHT;
    }
    if (first.column > second.column && first.row > second.row) {
        return Direction::DOWN_LEFT;
    }
    if (first.column < second.column && first.row > second.row) {
        return Direction::DOWN_RIGHT;
    }
    throw std::logic_error("Error. first == second!");
}
