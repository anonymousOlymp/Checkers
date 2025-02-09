#ifndef GAME_H
#define GAME_H

#include <memory>
#include <ostream>
#include <queue>

#include "player.h"
class Game {
public:
    Game(std::ostream &out, std::ostream &err, std::istream &in) :
        out_(out), err_(err), in_(in) {}
    Game(Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game &) = delete;
    Game &&operator=(Game &&) = delete;
    ~Game() = default;

    void choose_side();
    void move();
    bool is_over() const;
    void print_result() const;

private:
    std::queue<std::shared_ptr<Player>> players_;
    Board board_;
    std::ostream &out_;
    std::ostream &err_;
    std::istream &in_;
};

#endif // GAME_H
