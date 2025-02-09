#ifndef PLAYER_H
#define PLAYER_H

#include <ostream>
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
    explicit HumanPlayer(Board &board, std::ostream &out, std::ostream &err,
                         std::istream &in) noexcept
        : Player(board), out_(out), err_(err), in_(in) {}
    HumanPlayer(const HumanPlayer &) = delete;
    HumanPlayer(HumanPlayer &&) noexcept = delete;
    HumanPlayer &operator=(const HumanPlayer &) = delete;
    HumanPlayer &operator=(HumanPlayer &&) noexcept = delete;
    ~HumanPlayer() noexcept override = default;

    void move() override;

private:
    std::ostream &out_;
    std::ostream &err_;
    std::istream &in_;

    bool is_move_correct(const Move &move, const Positions &necessary_to_move,
                         const Positions &able_to_move,
                         bool &was_king_produced);
    bool try_move(Position position, Position goal, Direction direction,
                  bool need_eat, bool &is_king, Positions eaten) const;
};

class ComputerPlayer : public Player {
public:
    explicit ComputerPlayer(Board &board, std::ostream &out) noexcept
        : Player(board), mt_(device_()), out_(out) {}
    ComputerPlayer(const ComputerPlayer &) = delete;
    ComputerPlayer(ComputerPlayer &&) noexcept = delete;
    ComputerPlayer &operator=(const ComputerPlayer &) = delete;
    ComputerPlayer &operator=(ComputerPlayer &&) noexcept = delete;
    ~ComputerPlayer() noexcept override = default;

    void move() override;

private:
    std::random_device device_;
    std::mt19937 mt_;
    std::ostream &out_;

    void eat_all(Move &chosen, Direction &direction, Positions &eaten,
                 bool &is_king);
};

#endif  // PLAYER_H
