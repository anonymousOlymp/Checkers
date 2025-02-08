#ifndef GAME_H
#define GAME_H

#include <memory>
class Game {
public:
    Game() = default;
    Game(Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game &) = delete;
    Game &&operator=(Game &&) = delete;
    ~Game() = default;

    void choose_side();
    void move_white();
    void move_black();
    bool is_over() const;
    void print_result() const;

private:
    std::shared_ptr<Player> white_player = nullptr;
    std::shared_ptr<Player> black_player = nullptr;
    Board board;
};

#endif // GAME_H
