#include "GameFunctions.hpp"

#define EMPTY ' '

GameFunctions::GameFunctions(int grid_x, int grid_y, int num_mines)
                        : GenerateMineField(grid_x, grid_y, num_mines)
{
    // Create game_map to hold the current game state
    this->game_map = new char*[this->grid_y];
    for (int i = 0; i < grid_y; i++) this->game_map[i] = new char[this->grid_x];

    // Fill game_map with ' ' (EMPTY)
    std::fill(&game_map[0][0], &game_map[0][0] + grid_x * grid_y, EMPTY);
}

// Is called by area_reveal(), can be used as needed
PositionType GameFunctions::check_position(Coordinate selected_position)
{
    // Checks the selected position and assigns it to a PositionType

    PositionType curr_pos;
    int pos_num = this->num_field[selected_position.x][selected_position.y];

    if (pos_num == -1) curr_pos = is_mine;
    if (pos_num == 0) curr_pos = is_zero;
    else curr_pos = is_num;

    return curr_pos;
}

// GenerateMineField::fill_num_field() must be run first
bool GameFunctions::area_reveal(Coordinate selected_position)
{
    /*
    * Returns false if a mine has not been selected
    * If a mine is selected then display all other mines
    * If a num is selected display only that num
    * If a zero is selected then reveal all connected zeros
    */

    bool gameover = false;

    // Get the position type
    PositionType pos_type = this->check_position(selected_position);

    // Floodfill to get all connected zeros
    if (pos_type == is_zero) 
    {
        this->floodfill_zeroes(selected_position);
    }
    else if (pos_type == is_mine)
    {
        // The game is now over
        gameover = true;

        // Reveal bombs - @ for the selected bomb and # for all others
        this->game_map[selected_position.x][selected_position.y] = '@';

        for (int y = 0; y < this->grid_y; y++) {
            for (int x = 0; x < this->grid_x; x++) {
                if (this->mine_layout[x][y]) this->game_map[x][y] = '#';
            }
        }
    }
    else 
    {
        this->game_map[selected_position.x][selected_position.y] = 
            this->num_field[selected_position.x][selected_position.y];
    }

    return gameover;
}

void GameFunctions::floodfill_zeroes(Coordinate selected_position) {}


GameFunctions::~GameFunctions() 
{
    // Deallocate the game_map array
    if (this->game_map != nullptr) {
        for (int i = 0; i < this->grid_y; ++i) {
            delete[] this->game_map[i]; // Deallocate each row
        }
        delete[] this->game_map; // Deallocate the array of pointers
        this->game_map = nullptr; // Set to nullptr for safety
    }
}