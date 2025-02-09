#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "board.h"

class Player {
public:
    virtual ~Player() noexcept = default;

    virtual void move(Board &board) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer() noexcept = default;
    HumanPlayer(const HumanPlayer &) = default;
    HumanPlayer(HumanPlayer &&) noexcept = default;
    HumanPlayer &operator=(const HumanPlayer &) = default;
    HumanPlayer &operator=(HumanPlayer &&) noexcept = default;
    ~HumanPlayer() noexcept override = default;

    void move(Board &board) override;
private:
    bool is_move_correct(const std::string &current_position, const std::string &next_position, const std::vector<Position> &checkers_necessary_to_move, const std::vector<Position> &checkers_able_to_move);
};

class ConsolePlayer : public Player {
public:
    ConsolePlayer() noexcept = default;
    ConsolePlayer(const ConsolePlayer &) = default;
    ConsolePlayer(ConsolePlayer &&) noexcept = default;
    ConsolePlayer &operator=(const ConsolePlayer &) = default;
    ConsolePlayer &operator=(ConsolePlayer &&) noexcept = default;
    ~ConsolePlayer() noexcept override = default;

    void move(Board &board) override;
private:
    
};

#endif // PLAYER_H
