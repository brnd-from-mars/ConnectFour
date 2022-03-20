//
// Created by Brendan Berg on 08.03.22.
//

#pragma once

#include <SFML/Graphics.hpp>


class EventObserver
{

public:

    virtual bool HandleFocusReset() = 0;

    virtual bool Handle(sf::Event event) = 0;


};
