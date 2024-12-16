#ifndef ASSIGN_GENERATEMINEFIELD_HPP
#define ASSIGN_GENERATEMINEFIELD_HPP

#include <random>
#include <ctime>
#include <algorithm>
#include <list>

#include "../Utils/arrayUtils.hpp"
#include "../Utils/configDefs.hpp"

class GenerateMineField 
{
    protected:
        /* Grid Dimensions */
        int grid_x;
        int grid_y;

        /* Number of Mines */
        int num_mines;

        /* Random Generator */
        std::default_random_engine rand_engine;

        /* MineField */
        bool** mine_layout; // If loc has mine then True - Stores Mines
        int** num_field; // The number of mines close to each grid square - 0 is none

    public:
        /* Constructor */
        GenerateMineField(int grid_x, int grid_y, int num_mines);

        /* Destructor */
        virtual ~GenerateMineField();

        /* MineField Creation Methods */
        void place_mines(int mines_remaining); // Uses mine_layout and num_mines
        void fill_num_field();
};

#endif // ASSIGN_GENERATEMINEFIELD_HPP