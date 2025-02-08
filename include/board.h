#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <utility>

class Board {
public:
    enum class State { DRAW, PLAYING, WHITE_WON, BLACK_WON };

    Board();
    Board(const Board &) = default;
    Board(Board &&) noexcept = default;
    Board &operator=(const Board &) = default;
    Board &operator=(Board &&) noexcept = default;
    ~Board() noexcept = default;

    operator std::string() const;
    State get_state() const noexcept;
    bool try_move(Position first, Position second);
    void random_move();
private:
    State state_ = State::PLAYING;
};

#endif // BOARD_H
