#ifndef GAME_H
#define GAME_H

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
    void print_results() const;

private:
};

#endif // GAME_H
