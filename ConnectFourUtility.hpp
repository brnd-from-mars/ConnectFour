//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include <string>

#include <SFML/Graphics.hpp>


struct GameData
{
    std::string winningPlayer;
    std::string loosingPlayer;
    int moves;
    int time;
};


struct PlayerData
{
    std::string name;
    int games;
    int victories;
};


namespace ColorPalette
{
    const sf::Color Basestar = sf::Color(12, 20, 31);
    const sf::Color BasestarDark = sf::Color(8, 13, 21);
    const sf::Color BasestarLight = sf::Color(16, 27, 41);

    const sf::Color Orange = sf::Color(233, 126, 22);
    const sf::Color Cyan = sf::Color(0, 255, 255);
    const sf::Color Pane = sf::Color(230,255,255);
    const sf::Color SweetYellow = sf::Color(255,230,77);
    const sf::Color Gray = sf::Color(85,85,85);
    const sf::Color DarkBlue = sf::Color(6,36,116);
    const sf::Color PrussianBlue = sf::Color(0,49,83);
    const sf::Color Pred = sf::Color(255, 0, 85);
}


// TODO: add fonts
// TODO: add view coordinates and sizes