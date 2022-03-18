//
// Created by Florian Wolff on 11.03.22.
//

#include <string>

#include "ScoreBoardView.hpp"

#include "AppDelegate.hpp"
#include "ConnectFourUtility.hpp"


ScoreBoardView::ScoreBoardView(float x, float y, float width)
    : m_X(x), m_Y(y), m_Width(width)
{
    if (!m_Font.loadFromFile("Standard.ttf"))
    {
        throw std::runtime_error("Font Standard.ttf not loaded");
    }

    m_HeadlineShape.setFont(m_Font);
    m_HeadlineShape.setCharacterSize(20);
    m_HeadlineShape.setFillColor(ColorPalette::Basestar);
    m_HeadlineShape.setOutlineThickness(2.0f);
    m_HeadlineShape.setOutlineColor(ColorPalette::Orange);
    m_HeadlineShape.setPosition(sf::Vector2f(x, y));
    m_HeadlineShape.setString("XXXXX");

    for (int i = 0; i < 5; ++i)
    {
        auto lineY = LineToY(i);

        m_PlacingShapes[i].setFont(m_Font);
        m_PlacingShapes[i].setCharacterSize(15);
        m_PlacingShapes[i].setFillColor(ColorPalette::Orange);
        m_PlacingShapes[i].setString(std::to_string(i + 1).append("."));
        auto placingX = x + 10.0f - m_PlacingShapes->getGlobalBounds().width;
        m_PlacingShapes[i].setPosition(sf::Vector2f(placingX, lineY + 2.0f));

        m_NameShapes[i].setFont(m_Font);
        m_NameShapes[i].setCharacterSize(15);
        m_NameShapes[i].setFillColor(ColorPalette::Basestar);
        m_NameShapes[i].setOutlineThickness(2.0f);
        m_NameShapes[i].setOutlineColor(ColorPalette::Orange);
        m_NameShapes[i].setString("XXX");
        m_NameShapes[i].setPosition(sf::Vector2f(x + 20.0f, lineY));

        m_ScoreShapes[i].setFont(m_Font);
        m_ScoreShapes[i].setCharacterSize(15);
        m_ScoreShapes[i].setFillColor(ColorPalette::Basestar);
        m_ScoreShapes[i].setOutlineThickness(2.0f);
        m_ScoreShapes[i].setOutlineColor(ColorPalette::Orange);
        m_ScoreShapes[i].setString("X");
        auto scoreX = x + width - m_ScoreShapes->getGlobalBounds().width;
        m_ScoreShapes[i].setPosition(sf::Vector2f(scoreX, lineY));
    }
}


void ScoreBoardView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_Box);
    AppDelegate::Get()->GetWindow()->draw(m_HeadlineShape);

    for (const auto & placingShape : m_PlacingShapes)
    {
        AppDelegate::Get()->GetWindow()->draw(placingShape);
    }
    for (const auto & nameShape : m_NameShapes)
    {
        AppDelegate::Get()->GetWindow()->draw(nameShape);
    }
    for (const auto & scoreShape : m_ScoreShapes)
    {
        AppDelegate::Get()->GetWindow()->draw(scoreShape);
    }
}


bool ScoreBoardView::HandleFocusReset()
{
	return false;
}


bool ScoreBoardView::Handle(sf::Event event)
{
	return false;
}


float ScoreBoardView::LineToY(int line) const
{
    return m_Y + 50.0f + (line * 25.0f);
}


void ScoreBoardView::SetLine(int line, const std::string& name, const std::string& score)
{
    m_NameShapes[line].setString(name);
    m_ScoreShapes[line].setString(score);
    auto scoreX = m_X + m_Width - m_ScoreShapes[line].getGlobalBounds().width;
    m_ScoreShapes[line].setPosition(sf::Vector2f(scoreX, LineToY(line)));
}


void ScoreBoardView::SetHeadline(const std::string& headline)
{
    m_HeadlineShape.setString(headline);
}
