#ifndef ARRAY_UTIL_HPP
#define ARRAY_UTIL_HPP

#include <iostream>
#include <typeinfo>
#include <list>

// Template function to print a 2D array
template <typename T>
void printArray(int width, int length, T** array)
{
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << array[x][y] << " ";
        }
        std::cout << std::endl;
    }
}

struct Coordinate {
    int x;
    int y;

        // Operator to compare two Coordinates
    bool operator==(const Coordinate& rhs) const {
        return (this->x == rhs.x && this->y == rhs.y);
    }

    // Operator to compare two Coordinates
    bool operator!=(const Coordinate& rhs) const {
        return (this->x != rhs.x || this->y != rhs.y);
    }

    // Check if all values in Coordinate are greater than Coordinate rhs
    bool operator>(const Coordinate& rhs) {
        return (this->x > rhs.x && this->y > rhs.y);
    }

    // Check if all values in Coordinate are less than Coordinate rhs
    bool operator<(const Coordinate& rhs) {
        return (this->x < rhs.x && this->y < rhs.y);
    }

    // Check if all values in Coordinate are greater than Coordinate rhs
    bool operator>=(const Coordinate& rhs) {
        return (this->x >= rhs.x && this->y >= rhs.y);
    }

    // Check if all values in Coordinate are less than Coordinate rhs
    bool operator<=(const Coordinate& rhs) {
        return (this->x <= rhs.x && this->y <= rhs.y);
    }

    // Operator to add two Coordinates
    Coordinate& operator+=(const Coordinate& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    // Operator to subtract two Coordinates
    Coordinate& operator-=(const Coordinate& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    // Assignment operator - inline
    Coordinate& operator=(const Coordinate& rhs) {
        if (this != &rhs) {  
            this->x = rhs.x;
            this->y = rhs.y;
        }
        return *this;
    }

    // Operator to add two Coordinates - inline
    Coordinate operator+(const Coordinate& rhs) const {
        return Coordinate{this->x + rhs.x, this->y + rhs.y};
    }

    // Operator to subtract two Coordinates - inline
    Coordinate operator-(const Coordinate& rhs) const {
        return Coordinate{this->x - rhs.x, this->y - rhs.y};
    }

    // Operator to multiplier a Coordinate by a multiplier - inline
    Coordinate operator*(const int multiplier) const {
        return Coordinate{this->x * multiplier, this->y * multiplier};
    }

    // Operator to get the modulus of a Coordinate - inline
    Coordinate operator%(const int modulo) const {
        return Coordinate{this->x % modulo, this->y % modulo};
    }

    // Operator to easily print a Coordinate (mostly for debugging)
    friend std::ostream& operator<<(std::ostream& out, const Coordinate& cord) {
        return out << "(" << cord.x << ", " << cord.y << ")";
    }

};

// Pre-defined Coordinates to help traverse within the arrays
#define MOVE_NONE Coordinate{0, 0}
#define MOVE_UP Coordinate{-1, 0}
#define MOVE_UP_RIGHT Coordinate{-1, 1}
#define MOVE_RIGHT Coordinate{0, 1}
#define MOVE_DOWN_RIGHT Coordinate{1, 1}
#define MOVE_DOWN Coordinate{1, 0}
#define MOVE_DOWN_LEFT Coordinate{1, -1}
#define MOVE_LEFT Coordinate{0, -1}
#define MOVE_UP_LEFT Coordinate{-1, -1}

const std::list<Coordinate> POSSIBLE_MOVES = {MOVE_UP, MOVE_UP_RIGHT, 
                                                MOVE_RIGHT, MOVE_DOWN_RIGHT, 
                                                MOVE_DOWN, MOVE_DOWN_LEFT, 
                                                MOVE_LEFT, MOVE_UP_LEFT
                                                };

#endif // ARRAY_UTIL_HPP
