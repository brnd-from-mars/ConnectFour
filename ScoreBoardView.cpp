#include "ScoreBoardView.hpp"
#include "AppDelegate.hpp"
#include "TextFieldController.hpp"
#include <iostream>
#include <string>

ScoreBoardView::ScoreBoardView(float x, float y) {

    if (!m_Standard.loadFromFile("Standard.ttf"))
    {
        throw std::runtime_error("FAIL!");
    }

    m_TypeShape.setFont(m_Standard);
    m_TypeShape.setCharacterSize(20);
    m_TypeShape.setPosition(sf::Vector2f(x , y));
    m_TypeShape.setFillColor(sf::Color::Black);
    m_TypeShape.setOutlineThickness(2.f);
    m_TypeShape.setOutlineColor(ColorPalette::Orange);

    for (int i = 0;i < 5; i++) {
        m_NumberShape[i].setFont(m_Standard);
        m_NumberShape[i].setCharacterSize(15);
        m_NumberShape[i].setPosition(sf::Vector2f(x-6, 10+y+(i*20)));
        m_NumberShape[i].setFillColor(sf::Color::Black);
        m_NumberShape[i].setOutlineThickness(2.f);
        m_NumberShape[i].setOutlineColor(ColorPalette::Orange);
        m_Number[i] = std::to_string(i + 1);
        m_NumberShape[i].setString(m_Number[i]);
    }
    
    for (int i = 0;i < 5; i++) {
        m_NameShape[i].setFont(m_Standard);
        m_NameShape[i].setCharacterSize(15);
        m_NameShape[i].setPosition(sf::Vector2f(x+10, 10 + y + (i * 20)));
        m_NameShape[i].setFillColor(sf::Color::Black);
        m_NameShape[i].setOutlineThickness(2.f);
        m_NameShape[i].setOutlineColor(ColorPalette::Orange);
        m_NameShape[i].setString(m_Name[i]);
    }

    for (int i = 0;i < 5; i++) {
        m_ScoreShape[i].setFont(m_Standard);
        m_ScoreShape[i].setCharacterSize(15);
        m_ScoreShape[i].setPosition(sf::Vector2f(x+100, 10 + y + (i * 20)));
        m_ScoreShape[i].setFillColor(sf::Color::Black);
        m_ScoreShape[i].setOutlineThickness(2.f);
        m_ScoreShape[i].setOutlineColor(ColorPalette::Orange);
        m_ScoreShape[i].setString(m_Score[i]);
    }
}


void ScoreBoardView::SetList(std::string Name[5], std::string Score[5]) {
    for (int i = 0;i < 5;i++) {
        m_Name[i] = Name[i];
        m_NameShape[i].setString(m_Name[i]);
    }
    for (int i = 0;i < 5;i++) {
        m_Score[i] = Score[i];
        m_ScoreShape[i].setString(m_Score[i]);
    }
}

void ScoreBoardView::SetType(float type) {
    m_type = type;
    if (m_type == "1") {
        m_TypeShape.setString("Siege nach Anzahl");
    }
    if (m_type == "2") {
        m_TypeShape.setString("Siege nach wenigsten Z�gen");
    }
    if (m_type == "3") {
        m_TypeShape.setString("Siege nach Zeit");
    }
}

void ScoreBoardView::Draw() {

    AppDelegate::Get()->GetWindow()->draw(m_TypeShape);
    for (int i = 0;i < 5;i++) {
        AppDelegate::Get()->GetWindow()->draw(m_NumberShape[i]);
    }
    for (int i = 0;i < 5;i++) {
        AppDelegate::Get()->GetWindow()->draw(m_NameShape[i]);
    }
    for (int i = 0;i < 5;i++) {
        AppDelegate::Get()->GetWindow()->draw(m_ScoreShape[i]);
    }
    
}

void ScoreBoardView::SetText(std::string Text) {

}

bool ScoreBoardView::HandleFocusReset() {
	return false;
}

bool ScoreBoardView::Handle(sf::Event event) {
	return false;
}

void ScoreBoardView::UpdateView() {
  
}