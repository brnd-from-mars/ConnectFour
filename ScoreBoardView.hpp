//
// Created by Florian Wolff on 15.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"


class ScoreBoardView : public BaseView
{
public:

    ScoreBoardView(float x, float y, float width);

    void Draw() override;

    bool HandleFocusReset() override;
    bool Handle(sf::Event event) override;


private:

    void SetList(const std::string* names, const std::string* scores);
    void SetHeadline(const std::string& headline);
    void UpdateView();

    float m_X;
    float m_Y;
    float m_Width;

    sf::RectangleShape m_Box;
    sf::Text m_HeadlineShape;

    sf::Text m_PlacingShapes[5];
    sf::Text m_NameShapes[5];
    sf::Text m_ScoreShapes[5];

    sf::Font m_Font;


};
