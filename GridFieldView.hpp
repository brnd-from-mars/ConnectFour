//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class GridFieldController;


class GridFieldView : public BaseView
{
    friend GridFieldController;


public:

    GridFieldView(float x, float y);

    void Draw() override;

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;


private:

    sf::Vector2f GetCenter() const;

    std::weak_ptr<GridFieldController> m_GridFieldController;

    sf::RectangleShape m_FieldShape;

    static constexpr float m_Size = 25.0;
    static constexpr float m_Outline = 1.0;


};
