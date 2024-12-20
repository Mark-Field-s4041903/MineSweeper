#include "GameGUI.hpp"

GameGUI::GameGUI(int grid_x, int grid_y, int num_mines)
                        : GameFunctions(grid_x, grid_y, num_mines)
{
    // Create a new window
    this->window = new sf::RenderWindow(
        sf::VideoMode(this->grid_x * CELL_SIZE, this->grid_y * CELL_SIZE), WINDOW_NAME);

    // Create the base_grid as a 2D array of sf::RectangleShape
    this->base_grid = new sf::RectangleShape*[this->grid_x];
    for (int x = 0; x < grid_x; ++x) {
        this->base_grid[x] = new sf::RectangleShape[this->grid_y];
    }

    // Create the text_grid as a 2D array of sf::Text
    this->text_grid = new sf::Text*[this->grid_x];
    for (int x = 0; x < grid_x; ++x) {
        this->text_grid[x] = new sf::Text[this->grid_y];
    }

    // Set a font
    if (!this->font.loadFromFile(FONT_PATH))
    {
        throw std::runtime_error("!!! FONT LOADING FAILED !!! - "  + std::string(FONT_PATH));
    }


    // Initialize base_grid and text_grid with default shapes and text
    for (int y = 0; y < grid_y; ++y) {
        for (int x = 0; x < grid_x; ++x) {

            // Initialize base_grid
            this->base_grid[x][y].setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
            this->base_grid[x][y].setPosition(x * CELL_SIZE, y * CELL_SIZE);
            this->base_grid[x][y].setFillColor(CELL_BASE_COLOUR);
            this->base_grid[x][y].setOutlineThickness(OUTLINE_THICKNESS);
            this->base_grid[x][y].setOutlineColor(CELL_OUTLINE);

            // Initialize text_grid
            this->text_grid[x][y].setFont(this->font);
            this->text_grid[x][y].setString(" ");
            this->text_grid[x][y].setCharacterSize(TEXT_SIZE);
            this->text_grid[x][y].setFillColor(TEXT_COLOUR);
            this->text_grid[x][y].setPosition(
                x * CELL_SIZE + (CELL_SIZE / 2),
                y * CELL_SIZE + (CELL_SIZE / 2)
            );
        }
    }
}

void GameGUI::map_update()
{
    /*
    * Uses the game_map from GameFunctions to update the map displayed in the gui
    * Mostly only edits the text_grid
    */

    for (int y = 0; y < grid_y; ++y) {
        for (int x = 0; x < grid_x; ++x) {

            // Update the text in the cell
            char current_char = this->game_map[x][y];
            this->text_grid[x][y].setString(std::string(1, current_char));

            // If the square has now been revealed then change the colour
            if (this->game_map[x][y] != EMPTY_CHAR && this->game_map[x][y] != UNKNOWN_CHAR)
            {
                this->base_grid[x][y].setFillColor(CELL_BACKGROUND);
            }

            // Adjust text position for centering
            sf::FloatRect bounds = this->text_grid[x][y].getLocalBounds();
            this->text_grid[x][y].setPosition(
                x * CELL_SIZE + (CELL_SIZE - bounds.width) / 2 - bounds.left,
                y * CELL_SIZE + (CELL_SIZE - bounds.height) / 2 - bounds.top
            );
        }
    }
}

bool GameGUI::get_events()
{
    /*
    * Checks to see if the window has recieved any events
    * If the window is closed then returns false
    */

    // Check for any events
    sf::Event event;
    while (this->window->pollEvent(event)) 
    {
        /* Types of events */

        // Window Closed
        if (event.type == sf::Event::Closed) this->window->close();

        // Cell was clicked
        else if (event.type == sf::Event::MouseButtonPressed) 
        {
            // Get the mouse click position
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);

            // Determine the grid cell clicked
            Coordinate pos_clicked = 
                Coordinate{mousePosition.x / CELL_SIZE, mousePosition.y / CELL_SIZE};

            // Ensure the click is within bounds
            if (pos_clicked < Coordinate{this->grid_x, this->grid_y} 
                && pos_clicked >= Coordinate{0, 0})
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    this->handle_cell_click(LEFT, pos_clicked);
                }
                else 
                {
                    this->handle_cell_click(RIGHT, pos_clicked);
                }
            }
        }
    }

    // Background color
    this->window->clear(sf::Color::Blue);

    // Check if the game is complete
    if (this->check_if_finished()) 
    {
        // Reveal bombs
        for (int x = 0; x < this->grid_x; x++) {
            for (int y = 0; y < this->grid_y; y++) {
                if (this->mine_layout[x][y]) 
                {
                    this->game_map[x][y] = WIN_MINE_CHAR;
                    this->base_grid[x][y].setFillColor(CELL_REVEALED_MIN_COLOUR);
                }
            }
        }
    }

    // Check for gameover
    else if (this->gameover)
    {
        // Reveal bombs - @ for the selected bomb and # for all others
        for (int x = 0; x < this->grid_x; x++) {
            for (int y = 0; y < this->grid_y; y++) {
                if (this->game_map[x][y] == HIT_MINE_CHAR 
                    || this->game_map[x][y] == GAMEOVER_DISPLAY_CHAR)
                {
                    this->base_grid[x][y].setFillColor(CELL_GAMEOVER_COLOUR);
                }
            }
        }
    }

    // Draw the base_grid in the window
    for (int x = 0; x < grid_x; ++x) {
        for (int y = 0; y < grid_y; ++y) {
            this->window->draw(this->base_grid[x][y]);
            this->window->draw(this->text_grid[x][y]);
        }
    }

    // Output everything tothe window
    this->window->display();

    return this->window->isOpen();
}


void GameGUI::handle_cell_click(ClickType click_type, Coordinate position_clicked)
{
    if (click_type == LEFT) this->area_reveal(position_clicked);
    else if (this->game_map[position_clicked.x][position_clicked.y] == UNKNOWN_CHAR)
    {
        this->game_map[position_clicked.x][position_clicked.y] = EMPTY_CHAR;
        this->base_grid[position_clicked.x][position_clicked.y].setFillColor(CELL_BASE_COLOUR);
    }
    else if (this->game_map[position_clicked.x][position_clicked.y] == EMPTY_CHAR)
    {
        this->game_map[position_clicked.x][position_clicked.y] = UNKNOWN_CHAR;
        this->base_grid[position_clicked.x][position_clicked.y].setFillColor(CELL_UNKNOWN_COLOUR);
    }
}