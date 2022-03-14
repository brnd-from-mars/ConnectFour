//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"


class ArrowView : public BaseView
{

public:

    static std::shared_ptr<ArrowView> MakeArrow(float x, float y, sf::Color color, int layer = 0);

    ArrowView(float x, float y, sf::Color color, int layer);

    void Draw() override;

    void SetPosition(float x, float y);

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;


private:

    sf::ConvexShape m_ArrowHead;
    sf::ConvexShape m_ArrowBody;


};

