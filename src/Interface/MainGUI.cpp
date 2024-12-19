#include "MainGUI.hpp"

MainGUI::MainGUI()
{
    this->window = new sf::RenderWindow(
        sf::VideoMode(this->grid_x * CELL_SIZE, this->grid_y * CELL_SIZE), WINDOW_NAME);
}

MainGUI::game_loop()
{
    while (this->game_gui == nullptr 
            || (this->manage_events() == true && window->check_if_finished()) )
    {
        if (this->game_gui != nullptr)
        {
            window->map_update();
        }
    }
}

void MainGUI::display_main_menu()
{

}

bool MainGUI::manage_events()
{   
    // If GameGUI is running then use the event manager from it
    if (this->game_gui != nullptr) this->game_gui->get_events();
    else
    {
        sf::Event event;
        while (this->window->pollEvent(event)) 
        {
            /* Types of events */

            // Window Closed
            if (event.type == sf::Event::Closed) this->window->close();

            // Entry field was clicked
            if (event.type == sf::Event::MouseButtonPressed) 
            {
                // Get the mouse click position
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);

                // Determine the grid cell clicked
                // Coordinate pos_clicked = 
                //     Coordinate{mousePosition.x / CELL_SIZE, mousePosition.y / CELL_SIZE};
            }

            // Text is entered
            if (event.type == sf::Event::TextEntered) 
            {
                // Handle text input
                if (event.text.unicode == '\b') { // Handle backspace
                    if (!userInput.empty()) {
                        userInput.pop_back();
                    }
                } else if (event.text.unicode < 128) { // Printable ASCII characters
                    userInput += static_cast<char>(event.text.unicode);
                }
        }
    }

    return this->window->isOpen();
}