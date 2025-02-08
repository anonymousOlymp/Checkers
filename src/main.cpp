#include <exception>
#include <iostream>

int main(int argc, const char** argv) {
    try {
        Game game;
        game.choose_side();
        do {
            game.move_white();
            game.move_black();
        } while (!game.is_over());
        game.print_result();
    } catch(std::exception &exception) {
        std::cerr << "Error. Unexpected exception: " << exception.what() << std::endl;
    }
    return 0;
}