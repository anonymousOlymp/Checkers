#include <iostream>
#include "board.h"

#include "game.h"

void Game::choose_side() {
    char side;
    for ( ;; ) {
        out_ << "Choose you side (W, B): " << std::flush;
        in_ >> side;
        if (side == 'W' || side == 'B') {
            if (side == 'W') {
                players_.push(std::make_shared<HumanPlayer>(board_, out_, err_, in_));
                players_.push(std::make_shared<ComputerPlayer>(board_, out_));
            }
            if (side == 'B') {
                players_.push(std::make_shared<ComputerPlayer>(board_, out_));
                players_.push(std::make_shared<HumanPlayer>(board_, out_, err_, in_));
            }
            board_.set_orientation(side);
            return;
        }
        err_ << "Error. " << side << " wasn't recognized."
            << "Please, try again!" << std::endl;
    }
}

void Game::move() {
    auto player = players_.front();
    players_.pop();
    player->move();
    players_.push(player);
}

bool Game::is_over() const {
    return board_.get_state() != Board::State::PLAYING;
}

void Game::print_result() const {
    out_ << "Game over!" << std::endl;
    if (board_.get_state() == Board::State::HUMAN_WON) {
        out_ << "You are won!" << std::endl;
    } else if (board_.get_state() == Board::State::COMPUTER_WON) {
        out_ << "Computer is won!" << std::endl;
    } else {
        out_ << "DRAW" << std::endl;
    }
}

