//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ChipController;


class ChipView : public BaseView
{
    friend ChipController;

public:

    ChipView(float x, float y);

    void SetFillColor(sf::Color color);

    void EnableRing(bool enable);

    void Draw() override;

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;


private:

    std::weak_ptr<ChipController> m_ChipController;

    sf::CircleShape m_Circle;

    sf::CircleShape m_Ring;

    bool m_RingEnabled = false;

    static constexpr float m_InnerRadius = 21.0f;

    static constexpr float m_OuterRadius = 24.0f;


};
