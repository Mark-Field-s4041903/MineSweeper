#include <iostream>

#include "GameFunctions.hpp"


int main(int argc, char** argv) {
    int size_x;
    int size_y;
    int num_mines;

    int x, y;

    std::cin >> size_x >> size_y >> num_mines;

    GameFunctions *field = new GameFunctions(size_x, size_y, num_mines);

    field->place_mines(num_mines); 
    field->fill_num_field();

    bool gameover = false;
    bool completed = false;
    field->display_current_map();
    
    while (!gameover || completed) {
        std::cin >> x >> y;
        gameover = field->area_reveal(Coordinate{x, y});
        completed = field->check_if_finished();
        field->display_current_map();
    }

    return EXIT_SUCCESS;
}