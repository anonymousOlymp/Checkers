#include "checker.h"

const Position &Checker::get_position() const {
    return position_;
}

void Checker::set_position(Position position) {
    position_ = position;
}

bool Checker::is_king() const {
    return is_king_;
}

void Checker::set_king() {
    is_king_ = true;
}

char Checker::get_side() const {
    return side_;
}
