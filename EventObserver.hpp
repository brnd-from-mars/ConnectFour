//
// Created by Brendan Berg on 08.03.22.
//

#pragma once

#include <SFML/Graphics.hpp>

class AppDelegate; // forward-declaration to avoid cyclic include


class EventObserver
{

public:

    virtual bool ResetFocus() = 0;

    virtual bool Handle(sf::Event event) = 0;


};
