#pragma once
#include "BaseView.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class ScoreBoardView : public BaseView
{ 
public:
    ScoreBoardView(float x, float y);
    void Draw() override;
    bool HandleFocusReset() override;
    bool Handle(sf::Event event) override;
    void SetText(std::string Text); //Altered to SetList to display the ScoreBoard
    void SetList(std::string Name[5], std::string Score[5]);
    void SetType(float type);
    void UpdateView();

private:
    
    std::string m_Name[5];
    sf::Text m_NameShape[5];

    std::string m_Score[5];
    sf::Text m_ScoreShape[5];

    std::string m_Number[5];
    sf::Text m_NumberShape[5];

    std::string m_type;
    sf::Text m_TypeShape;

    sf::Font m_Standard;

    bool m_focus = false;
};

