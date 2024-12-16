#ifndef ASSIGN_GAMEFUNCTIONS_HPP
#define ASSIGN_GAMEFUNCTIONS_HPP

#include <iostream>

#include "GenerateMineField.hpp"
#include "../Utils/configDefs.hpp"

enum PositionType {
    is_mine = -1,  // Represents a mine
    is_zero = 0,   // Represents zero mines around
    is_num = 1     // Represents positions with (a) adjacent mine(s)
};

class GameFunctions : public GenerateMineField
{
    public:
        /* Constructor */
        GameFunctions(int grid_x, int grid_y, int num_mines);
        
        /* Deconstructor */
        ~GameFunctions();
        
        /* The current map */
        char** game_map;

        /* Game Functions */
        bool area_reveal(Coordinate selected_position);
        void display_current_map();
        bool check_if_finished();

    private:
        PositionType check_position(Coordinate selected_position);
        void floodfill_zeroes(Coordinate current_pos);
};

#endif //ASSIGN_GAMEFUNCTIONS_HPP