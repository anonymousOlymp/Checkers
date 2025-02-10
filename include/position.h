#ifndef POSITION_H
#define POSITION_H

#include <functional>
#include <optional>
#include <string>

enum class Direction { UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };
std::vector<Direction> get_all_direction_values();

struct Position {
public:
    char column;  // TODO: to getter
    char row;

    Position(char column, char row) noexcept : column(column), row(row) {};

    static Position from_string(const std::string &position) noexcept;

    bool operator==(const Position &other) const;
    bool operator!=(const Position &other) const;
    operator bool() const;
};

struct Move {
public:
    Position first;  // TODO: to getter
    Position second;

    Move(Position first, Position second) noexcept
        : first(first), second(second) {}

    operator Direction() const;
};

using Operation = std::function<void(Position)>;  // TODO: remove

Position operator+(Position position, Direction direction);
bool apply_if_exists(Position position, Direction direction,
                     Operation o);  // TODO: remove
bool exists(Position position, Direction direction);

template <>
struct std::hash<Position> {
    std::size_t operator()(const Position &position) const noexcept {
        std::size_t h1 = std::hash<char>{}(position.column);
        std::size_t h2 = std::hash<char>{}(position.row);
        return h1 ^ (h2 << 1);
    }
};

#endif  // POSITION_H
