#ifndef CHECKER_H
#define CHECKER_H

#include "position.h"

class Checker {
public:
    explicit Checker(char side) noexcept
        : side_(side)
    {}
    Checker(const Checker &) = default;
    Checker(Checker &&) noexcept = default;
    Checker &operator=(const Checker &) = default;
    Checker &operator=(Checker &&) noexcept = default;
    ~Checker() noexcept = default;

    operator char() const;
    bool is_king() const;
    void set_king();
    char get_side() const;

private:
    char side_;
    bool is_king_ = false;
};

#endif // CHECKER_H
