#include "GameGUI.hpp"

GameGUI::GameGUI(int grid_x, int grid_y, int num_mines)
                        : GameFunctions(grid_x, grid_y, num_mines)
{
    // Create a new window
    this->window = new sf::RenderWindow(
        sf::VideoMode(this->grid_x * CELL_SIZE, this->grid_y * CELL_SIZE), WINDOW_NAME);

    // Create the base_grid with grid_y number of rows
    this->base_grid = new sf::RectangleShape*[this->grid_y];

    // Create grid_x number of columns
    for (int i = 0; i < grid_y; i++) {
        this->base_grid[i] = new sf::RectangleShape[this->grid_x];
    }

    // Create the text_grid with grid_y number of rows
    this->text_grid = new sf::Text*[this->grid_y];

    // Create text_grid number of columns
    for (int i = 0; i < grid_y; i++) {
        this->text_grid[i] = new sf::Text[this->grid_x];
    }

    // Set a font
    this->font.loadFromFile(FONT_PATH);
}

void GameGUI::map_update()
{
    for (int y = 0; y < grid_y; ++y) {
        for (int x = 0; x < grid_x; ++x) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2)); // Slightly smaller for base_grid lines
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);

            // Cell styling
            cell.setFillColor(CELL_COLOUR);
            cell.setOutlineThickness(OUTLINE_THICKNESS);
            cell.setOutlineColor(CELL_OUTLINE);

            // Add cell -Broken?
            this->base_grid[x][y] = cell;

            // Create the text for the cell
            sf::Text charText;
            charText.setFont(this->font);
            charText.setString(static_cast<std::string>("" + this->game_map[x][y]));  // Replace with your character
            charText.setCharacterSize(TEXT_SIZE);  // Adjust size as needed
            charText.setFillColor(TEXT_COLOUR);

            // Position the text in the center of the cell
            charText.setPosition(
                x * CELL_SIZE + (CELL_SIZE / 2) - (charText.getLocalBounds().width / 2),
                y * CELL_SIZE + (CELL_SIZE / 2) - (charText.getLocalBounds().height / 2)
                );

            // Store the text in the textGrid
            this->text_grid[x][y] = charText;
        }
    }
}

bool GameGUI::get_events()
{
    // Check for any events
    sf::Event event;
    while (this->window->pollEvent(event)) 
    {
        // Types of events
        if (event.type == sf::Event::Closed) this->window->close();
    }

    // Background color
    this->window->clear(sf::Color::Blue);

    // Draw the base_grid in the window
    for (int x = 0; x < grid_x; ++x) {
        for (int y = 0; y < grid_y; ++y) {
            this->window->draw(this->base_grid[x][y]);
            this->window->draw(this->text_grid[x][y]);
        }
    }

    this->window->display();

    return this->window->isOpen();
}