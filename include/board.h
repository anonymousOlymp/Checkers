#ifndef BOARD_H
#define BOARD_H

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "checker.h"
#include "position.h"

using Moves = std::vector<Move>;

class Board {
public:
    enum class State { DRAW, PLAYING, HUMAN_WON, COMPUTER_WON };
    using Functor = std::function<void(Position, const Checker &)>;

    Board();
    Board(const Board &) = default;
    Board(Board &&) noexcept = default;
    Board &operator=(const Board &) = default;
    Board &operator=(Board &&) noexcept = default;
    ~Board() noexcept = default;

    operator std::string() const;
    State get_state() const noexcept;
    void set_state(State state) noexcept;
    void process_human_checkers(const Functor &functor) const;
    void process_computer_checkers(const Functor &functor) const;
    void process_checkers(const Functor &functor) const;
    bool has_computer_checker(Position position) const;
    bool has_human_checker(Position position) const;
    bool has_checker(Position position) const;
    void remove_checker(Position position);
    void add_checker(Position position, Checker checker);
    const Checker &get_checker(Position position) const;
    Moves get_free_moves(Position position) const;
    Moves get_eat_moves(Position position) const;
    Moves get_king_eat_moves(Position position) const;

private:
    State state_ = State::PLAYING;
    std::unordered_map<Position, Checker> board_;
    char side_ = '\0';

    static std::vector<Position> get_neighbors_positions(Position position);
    char position_to_char(Position position) const;
};

#endif  // BOARD_H
