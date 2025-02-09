#include <iostream>
#include "board.h"

#include "game.h"

void Game::choose_side() {
    char side;
    for ( ;; ) {
        std::cout << "Choose you side (W, B): " << std::flush;
        std::cin >> side;
        if (side == 'W' || side == 'B') {
            if (side == 'W') {
                players_.push(std::make_shared<HumanPlayer>(board_));
                players_.push(std::make_shared<ComputerPlayer>(board_));
            }
            if (side == 'B') {
                players_.push(std::make_shared<ComputerPlayer>(board_));
                players_.push(std::make_shared<HumanPlayer>(board_));
            }
            board_.set_orientation(side);
            return;
        }
        std::cerr << "Error. " << side << " wasn't recognized."
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
    std::cout << "Game over!" << std::endl;
    if (board_.get_state() == Board::State::HUMAN_WON) {
        std::cout << "You are won!" << std::endl;
    } else if (board_.get_state() == Board::State::COMPUTER_WON) {
        std::cout << "Computer is won!" << std::endl;
    } else {
        std::cout << "DRAW" << std::endl;
    }
}

