#include "GameFunctions.hpp"

#define EMPTY_CHAR ' '

GameFunctions::GameFunctions(int grid_x, int grid_y, int num_mines)
                        : GenerateMineField(grid_x, grid_y, num_mines)
{
    // Create game_map to hold the current game state
    this->game_map = new char*[this->grid_y];

    // Fill game_map with ' ' (EMPTY_CHAR)
    for (int i = 0; i < grid_y; i++) {
        this->game_map[i] = new char[this->grid_x];
        std::fill(this->game_map[i], this->game_map[i] + this->grid_x, EMPTY_CHAR);
    }
}

// Is called by area_reveal(), can be used as needed
PositionType GameFunctions::check_position(Coordinate selected_position)
{
    // Checks the selected position and assigns it to a PositionType

    PositionType curr_pos_type;
    int pos_num = this->num_field[selected_position.x][selected_position.y];

    if (pos_num == -1) curr_pos_type = is_mine;
    else if (pos_num == 0) curr_pos_type = is_zero;
    else curr_pos_type = is_num;

    return curr_pos_type;
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
        // this->game_map[selected_position.x][selected_position.y] = '0';
    }
    else if (pos_type == is_mine)
    {
        std::cout << "GAMEOVER" << std::endl;
        // The game is now over
        gameover = true;

        // Reveal bombs - @ for the selected bomb and # for all others
        for (int x = 0; x < this->grid_x; x++) {
            for (int y = 0; y < this->grid_y; y++) {
                if (selected_position == Coordinate{x, y}) this->game_map[x][y] = 'X';
                else if (this->mine_layout[x][y]) this->game_map[x][y] = 'O';
            }
        }
    }
    else 
    {
        this->game_map[selected_position.x][selected_position.y] = 
            static_cast<char>('0' + this->num_field[selected_position.x][selected_position.y]);
    }

    return gameover;
}

void GameFunctions::floodfill_zeroes(Coordinate current_pos) 
{
    // Base case: not checked
    if (this->game_map[current_pos.x][current_pos.y] == EMPTY_CHAR) 
    {
        if (this->num_field[current_pos.x][current_pos.y] == 0) 
        {
            this->game_map[current_pos.x][current_pos.y] = '0';

            for (Coordinate move : POSSIBLE_MOVES) {
                Coordinate next_pos = current_pos + move;

                if (next_pos >= Coordinate{0, 0} 
                    && next_pos < Coordinate{this->grid_x, this->grid_y})
                {
                    this->floodfill_zeroes(next_pos);
                }
            }
        } 
        else 
        {
            this->game_map[current_pos.x][current_pos.y] = 
                static_cast<char>('0' + this->num_field[current_pos.x][current_pos.y]);
        }
    }
}

void GameFunctions::display_current_map() 
{
    for (int y = 0; y < this->grid_y; y++) {
        std::cout << '|';
        for (int x = 0; x < this->grid_x; x++) {
            std::cout << this->game_map[x][y] << '|';
        }
        std::cout << std::endl;
    }
}

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