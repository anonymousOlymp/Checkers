#ifndef POSITION_H
#define POSITION_H

#include <string>

enum class Direction { UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

struct Position {
public:
    const char column;
    const char row;

    Position(char column, char row) noexcept
        : column(column), row(row)
    {};
    
    explicit Position(std::string position) noexcept
        : column(position[0]), row(position[1])
    {};

    bool operator==(const Position &other) const;
    bool operator!=(const Position &other) const;
};

struct Move {
public:
    const Position first;
    const Position second;

    Move(Position first, Position second) noexcept
        : first(first), second(second)
    {}

    operator Direction() const;
};

Position operator+(Position position, Direction direction);
Position operator-(Position position, Direction direction);
Direction operator-(Position first, Position second);

#endif // POSITION_H
