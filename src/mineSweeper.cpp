#include <iostream>

#include "GenerateMineField.hpp"


int main(int argc, char** argv) {
    int size_x;
    int size_y;
    int num_mines;

    std::cin >> size_x >> size_y >> num_mines;

    GenerateMineField *field = new GenerateMineField(size_x, size_y, num_mines);

    field->place_mines(num_mines);
    field->fill_num_field();

    return EXIT_SUCCESS;
}