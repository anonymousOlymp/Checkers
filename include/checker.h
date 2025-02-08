#ifndef CHECKER_H
#define CHECKER_H

#include <utility>

using Position = std::pair<char, char>;

class Checker {
public:
    Checker(Position position, char side) noexcept
        : position_(position), side_(side)
    {}
    Checker(const Checker &) = default;
    Checker(Checker &&) noexcept = default;
    Checker &operator=(const Checker &) = default;
    Checker &operator=(Checker &&) noexcept = default;
    ~Checker() noexcept = default;

    const Position &get_position() const;
    void set_position(Position position);
    bool is_king() const;
    void set_king();
    char get_side() const;

private:
    Position position_;
    char side_;
    bool is_king_ = false;
};

#endif // CHECKER_H
