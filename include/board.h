#ifndef BOARD_H
#define BOARD_H

#include <functional>
#include <string>
#include <unordered_map>

#include "checker.h"
#include "position.h"

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
    std::vector<Move> get_free_move(Position position) const;
    std::vector<Position> get_enemy_neighbors(Position position) const;
    std::vector<Position> get_enemy_neighbors_of_king(Position position) const;

private:
    State state_ = State::PLAYING;
    std::unordered_map<Position, Checker> board_;
    char side_ = '\0';

    static std::vector<Position> get_neighbors_positions(Position position);
    char position_to_char(Position position) const;
};

#endif  // BOARD_H
