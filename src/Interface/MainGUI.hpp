#ifndef ASSIGN_MainGUI_HPP
#define ASSIGN_MainGUI_HPP

#include "../Utils/arrayUtils.hpp"
#include "../Utils/configDefs.hpp"
#include "GameGUI.hpp"

#include <SFML/Graphics.hpp>

class MainGUI
{
    public:
        MainGUI();

    private:
        sf::RenderWindow* window;
        GameGUI* game_gui  = nullptr;
        bool manage_events();


};

#endif //ASSIGN_MainGUI_HPP