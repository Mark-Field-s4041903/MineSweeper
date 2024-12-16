#include <iostream>

#include "Base/GameFunctions.hpp"
#include "Interface/GameGUI.hpp"

#define USE_TERMINAL 0


int main(int argc, char** argv) {
    int size_x;
    int size_y;
    int num_mines;

    int x, y;

    bool gameover = false;
    bool completed = false;

    std::cin >> size_x >> size_y >> num_mines;

    if (bool(USE_TERMINAL)) 
    {
        GameFunctions *field = new GameFunctions(size_x, size_y, num_mines);

        field->place_mines(num_mines); 
        field->fill_num_field();

        field->display_current_map();
        
        while (!gameover && !completed) {
            std::cin >> x >> y;
            gameover = field->area_reveal(Coordinate{x, y});
            completed = field->check_if_finished();
            field->display_current_map();
        }
    }
    else
    {
        GameGUI *window = new GameGUI(size_x, size_y, num_mines);
        window->place_mines(num_mines); 
        window->fill_num_field();

        window->map_update();
        while(window->get_events())
        {
            completed = window->check_if_finished();
            window->map_update();
        }
    }

    return EXIT_SUCCESS;
}