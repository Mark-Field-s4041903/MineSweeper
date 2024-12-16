#ifndef ASSIGN_GAMEGUI_HPP
#define ASSIGN_GAMEGUI_HPP

#include "../Base/GameFunctions.hpp"
#include <SFML/Graphics.hpp>
#include <string>

/* For the main window */
#define WINDOW_NAME "MineSweeper"
#define CELL_SIZE 32
#define OUTLINE_THICKNESS 1
#define CELL_COLOUR sf::Color::White
#define CELL_OUTLINE sf::Color::Black

/* For the text on the window */
#define FONT_PATH "src/Interface/Fonts/times.ttf"
#define TEXT_SIZE 24
#define TEXT_COLOUR sf::Color::Black


class GameGUI : public GameFunctions
{
    private:
        /* The window the game will be displayed in */
        sf::RenderWindow* window;

        /* A base_grid for the buttons */
        sf::RectangleShape** base_grid;

        /* An editable text_grid for the current state t be shown */
        sf::Text** text_grid;

        /* Set a font */
        sf::Font font;


    public:
        /* Constructor */
        GameGUI(int grid_x, int grid_y, int num_mines);

        /* Update Grid */
        void map_update();

        bool get_events();
};

#endif // ASSIGN_GAMEGUI_HPP