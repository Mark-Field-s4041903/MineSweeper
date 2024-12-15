#include "GenerateMineField.hpp"

GenerateMineField::GenerateMineField(int grid_x, int grid_y, int num_mines)
{
    // Add args into the class
    this->grid_x = grid_x;
    this->grid_y = grid_y;
    this->num_mines = num_mines;

    // Create mine_layout grid
    this->mine_layout = new bool*[this->grid_y];
    for (int i = 0; i < grid_y; i++) this->mine_layout[i] = new bool[this->grid_x];

    // Fill mine_layout with false
    std::fill(&mine_layout[0][0], &mine_layout[0][0] + grid_x * grid_y, false);

    // Create num_field grid
    this->num_field = new int*[this->grid_y];
    for (int i = 0; i < grid_y; i++) this->num_field[i] = new int[this->grid_x];

    // Fill num_field with 0 (None)
    std::fill(&num_field[0][0], &num_field[0][0] + grid_x * grid_y, NONE);

    // Create a seed sequence using the current time
    std::seed_seq seed_seq{static_cast<unsigned int>(std::time(0))};

    // Seed the random engine with the seed sequence
    this->rand_engine.seed(seed_seq);
}

void GenerateMineField::place_mines(int mines_remaining)
{
    /*
    * Recursively places the mines randomly within a grid
    * False means there is no mine
    * True means that a mine is in this location
    */

    if (mines_remaining > 0) 
    {
        int pos_x = this->rand_engine() % this->grid_x;
        int pos_y = this->rand_engine() % this->grid_y;

        if (this->mine_layout[pos_x][pos_y] == false)
        {
            this->mine_layout[pos_x][pos_y] = true;
            mines_remaining --;
        }
        place_mines(mines_remaining);
    }
}

// place_mines must be run first
void GenerateMineField::fill_num_field()
{   
    /*
    * Checks each position in the map and shows the number of mines adjacent to it
    */
    for (int y = 0; y < this->grid_y; y++) {
        for (int x = 0; x < this->grid_x; x++) {
            
            // Iterate through all adjacent positions and record the number of mines
            for (Coordinate move : POSSIBLE_MOVES) {
                Coordinate next_pos = Coordinate{x, y} + move;

                // Check to make sure the next position is inbounds
                // If there is a mine near it then increase the count
                if (next_pos >= Coordinate{0, 0} 
                    && next_pos < Coordinate{this->grid_x, this->grid_y}
                    && this->mine_layout[next_pos.x][next_pos.y]) 
                {
                    if (this->mine_layout[x][y]) this->num_field[x][y] = MINE;
                    else this->num_field[x][y] ++;
                }
            }
        }
    }
}

GenerateMineField::~GenerateMineField()
{
    // Deallocate the mine_layout array
    if (this->mine_layout != nullptr) {
        for (int i = 0; i < this->grid_y; ++i) {
            delete[] this->mine_layout[i]; // Deallocate each row
        }
        delete[] this->mine_layout; // Deallocate the array of pointers
        this->mine_layout = nullptr; // Set to nullptr for safety
    }

    // Deallocate the num_field array
    if (this->num_field != nullptr) {
        for (int i = 0; i < this->grid_y; ++i) {
            delete[] this->num_field[i]; // Deallocate each row
        }
        delete[] this->num_field; // Deallocate the array of pointers
        this->num_field = nullptr; // Set to nullptr for safety
    }
}