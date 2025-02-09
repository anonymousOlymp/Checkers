#ifndef PLAYER_H
#define PLAYER_H

#include <random>
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

using Positions = std::unordered_set<Position>;

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(Board &board) noexcept : Player(board) {}
    HumanPlayer(const HumanPlayer &) = delete;
    HumanPlayer(HumanPlayer &&) noexcept = delete;
    HumanPlayer &operator=(const HumanPlayer &) = delete;
    HumanPlayer &operator=(HumanPlayer &&) noexcept = delete;
    ~HumanPlayer() noexcept override = default;

    void move() override;

private:
    bool is_move_correct(const Move &move, const Positions &necessary_to_move,
                         const Positions &able_to_move);
    bool try_move(Position position, Position goal, Direction direction,
                  bool need_eat, bool is_king, Positions eaten) const;
};

class ComputerPlayer : public Player {
public:
    explicit ComputerPlayer(Board &board) noexcept
        : Player(board), mt_(device_()) {}
    ComputerPlayer(const ComputerPlayer &) = delete;
    ComputerPlayer(ComputerPlayer &&) noexcept = delete;
    ComputerPlayer &operator=(const ComputerPlayer &) = delete;
    ComputerPlayer &operator=(ComputerPlayer &&) noexcept = delete;
    ~ComputerPlayer() noexcept override = default;

    void move() override;

private:
    void eat_all(Move &chosen, Direction &direction, Positions &eaten);
    std::random_device device_;
    std::mt19937 mt_;
};

#endif  // PLAYER_H
