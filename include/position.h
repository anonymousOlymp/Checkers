#ifndef POSITION_H
#define POSITION_H

#include <functional>
#include <optional>
#include <string>

enum class Direction { UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

struct Position {
public:
    char column;
    char row;

    Position(char column, char row) noexcept
        : column(column), row(row)
    {};

    static Position from_string(const std::string &position) noexcept;

    bool operator==(const Position &other) const;
    bool operator!=(const Position &other) const;
    operator bool() const;
};

struct Move {
public:
    Position first;
    Position second;

    Move(Position first, Position second) noexcept
        : first(first), second(second)
    {}

    operator Direction() const;
};

using Operation = std::function<void (Position)>;

Position operator+(Position position, Direction direction);
bool apply_if_exists(Position position, Direction direction, Operation o);
bool exists(Position position, Direction direction);
Position operator-(Position position, Direction direction);
Direction operator-(Position first, Position second);

template<>
struct std::hash<Position>
{
    std::size_t operator()(const Position &position) const noexcept
    {
        std::size_t h1 = std::hash<char>{}(position.column);
        std::size_t h2 = std::hash<char>{}(position.row);
        return h1 ^ (h2 << 1);
    }
};

template<>
struct std::hash<Move>
{
    std::size_t operator()(const Move &move) const noexcept
    {
        std::size_t h1 = std::hash<Position>{}(move.first);
        std::size_t h2 = std::hash<Position>{}(move.second);
        return h1 ^ (h2 << 1);
    }
};

#endif // POSITION_H
