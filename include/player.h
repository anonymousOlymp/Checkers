#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    virtual ~Player() noexcept = default;

    virtual const std::string get_name() const noexcept = 0;
    virtual bool is_won() const = 0;
    virtual void move(Board &board) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer() noexcept = default;
    HumanPlayer(const HumanPlayer &) = default;
    HumanPlayer(HumanPlayer &&) noexcept = default;
    HumanPlayer &operator=(const HumanPlayer &) = default;
    HumanPlayer &operator=(HumanPlayer &&) noexcept = default;
    virtual ~HumanPlayer() noexcept = default;

    virtual const std::string get_name() const noexcept override;
    virtual bool is_won() const override;
    virtual void move(Board &board) override;
private:
    
};

class ConsolePlayer : public Player {
public:
    ConsolePlayer() noexcept = default;
    ConsolePlayer(const ConsolePlayer &) = default;
    ConsolePlayer(ConsolePlayer &&) noexcept = default;
    ConsolePlayer &operator=(const ConsolePlayer &) = default;
    ConsolePlayer &operator=(ConsolePlayer &&) noexcept = default;
    virtual ~ConsolePlayer() noexcept = default;

    virtual const std::string get_name() const noexcept override;
    virtual bool is_won() const override;
    virtual void move(Board &board) override;
private:
    
};

#endif // PLAYER_H
