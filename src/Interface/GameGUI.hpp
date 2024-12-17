#ifndef ASSIGN_GAMEGUI_HPP
#define ASSIGN_GAMEGUI_HPP

#include "../Base/GameFunctions.hpp"
#include "../Utils/arrayUtils.hpp"
#include "../Utils/configDefs.hpp"

#include <SFML/Graphics.hpp>
#include <exception>
#include <string>

enum ClickType {LEFT, RIGHT};

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

        /* Click Handling */
        void handle_cell_click(ClickType click_type, Coordinate position_clicked);

    public:
        /* Constructor */
        GameGUI(int grid_x, int grid_y, int num_mines);

        /* Destructor */
        ~GameGUI();
        
        /* GUI Management */
        void map_update();
        bool get_events();
};

#endif // ASSIGN_GAMEGUI_HPP