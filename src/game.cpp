#include <iostream>

#include "game.h"

void Game::choose_side() {
    char side;
    for ( ;; ) {
        std::cout << "Choose you side (W, B): " << std::flush;
        std::cin >> side;
        if (side == 'W' || side == 'B') {
            if (side == 'W') {
                white_player = std::make_shared<HumanPlayer>();
                black_player = std::make_shared<ConsolePlayer>();
            }
            if (side == 'B') {
                white_player = std::make_shared<ConsolePlayer>();
                black_player = std::make_shared<HumanPlayer>();
            }
            board.set_orientation(side);
            return;
        }
        std::cerr << "Error. " << side << " wasn't recognized."
            << "Please, try again!" << std::endl;
    }
}

void Game::move_white() {
    white_player->move(board)
}

void Game::move_black() {
    black_player->move(board);
}

bool Game::is_over() const {
    if (white_player->is_won()) {
        return true;
    }
    if (black_player->is_won()) {
        return true;
    }
    return board.is_stagnation();
}

void Game::print_result() const {
    std::cout << "Game over!" << std::endl;
    if (board.is_stagnation()) {
        std::cout << "DRAW" << std::endl;
    } else if (white_player->is_won()) {
        std::cout << white_player->name << "is won!" << std::endl;
    } else {
        std::cout << black_player->name << "is won!" << std::endl;
    }
}

