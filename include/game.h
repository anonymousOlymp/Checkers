#ifndef GAME_H
#define GAME_H

#include <memory>
#include <queue>

#include "player.h"
class Game {
public:
    Game() = default;
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
};

#endif // GAME_H
