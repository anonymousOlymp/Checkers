#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <functional>

#include "checker.h"

class Board {
public:
    enum class State { DRAW, PLAYING, HUMAN_WON, COMPUTER_WON };
    using Functor = std::function<void (*) (Checker)>;

    Board();
    Board(const Board &) = default;
    Board(Board &&) noexcept = default;
    Board &operator=(const Board &) = default;
    Board &operator=(Board &&) noexcept = default;
    ~Board() noexcept = default;

    operator std::string() const;
    State get_state() const noexcept;
    void set_state() noexcept;
    void process_human_checkers(Functor functor);
    void process_computer_checkers(Functor functor);
    void process_checkers(Functor functor);
    bool has_computer_checker(Position position);
    bool has_human_checker(Position position);
    bool has_checker(Position position);
    void remove_checker(Position position);
    void add_checker(Position position, Checker checker);
    Checker get_checker(Position position);
    std::vector<Move> get_free_move(Position position);
    std::vector<Position> get_enemy_neighbors(Position position);
    std::vector<Position> get_enemy_neighbors_of_king(Position position);
private:
    State state_ = State::PLAYING;
    
};

#endif // BOARD_H
