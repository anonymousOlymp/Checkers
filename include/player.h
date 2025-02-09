#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_set>

#include "board.h"
#include "position.h"

class Player {
public:
    Player(Board &board) noexcept : board_(board) {}
    virtual ~Player() noexcept = default;

    virtual void move() = 0;

protected:
    Board &board_;
};

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(Board &board) noexcept : Player(board) {}
    HumanPlayer(const HumanPlayer &) = default;
    HumanPlayer(HumanPlayer &&) noexcept = default;
    HumanPlayer &operator=(const HumanPlayer &) = delete;
    HumanPlayer &operator=(HumanPlayer &&) noexcept = delete;
    ~HumanPlayer() noexcept override = default;

    void move() override;
private:
    using Positions = std::unordered_set<Position>;

    bool is_move_correct(const Move &move, const Positions &necessary_to_move, const Positions &able_to_move);
    bool try_move(Position position, Position goal, Direction direction, bool need_eat, bool is_king, Positions eaten) const;
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
