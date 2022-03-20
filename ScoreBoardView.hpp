//
// Created by Florian Wolff on 11.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ScoreBoardController;


class ScoreBoardView : public BaseView
{
    friend ScoreBoardController;

public:

    ScoreBoardView(float x, float y, float width);

    void Draw() override;

    bool HandleFocusReset() override;
    bool Handle(sf::Event event) override;


private:

    float LineToY(int line) const;

    void SetLine(int line, const std::string& name, const std::string& score);
    void SetHeadline(const std::string& headline);

    float m_X;
    float m_Y;
    float m_Width;

    sf::Text m_HeadlineShape;

    sf::Text m_PlacingShapes[5];
    sf::Text m_NameShapes[5];
    sf::Text m_ScoreShapes[5];

    sf::Font m_Font;


};
