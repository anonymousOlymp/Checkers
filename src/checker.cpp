#include "checker.h"

bool Checker::is_king() const { return is_king_; }

void Checker::set_king() { is_king_ = true; }

char Checker::get_side() const { return side_; }

Checker::operator char() const {
    if (is_king()) {
        if (side_ == 'W') {
            return 'X';
        }
        return 'Y';
    }
    return side_;
}
