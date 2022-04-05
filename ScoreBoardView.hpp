//
// Created by Florian Wolff on 11.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ScoreBoardController;


/*!
 * @brief TextView displays a headline and the top 5 scores with their placement and player name on the screen.
 */
class ScoreBoardView : public BaseView
{
    friend ScoreBoardController;

public:

    /*!
     * @brief Constructor initializes all SFML elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width total width of the scoreboard
     */
    ScoreBoardView(float x, float y, float width);

    /*!
     * @brief Draws the scoreboard to the RenderWindow in the AppDelegate.
     */
    void Draw() override;

    /*!
     * @brief No-op.
     *
     * @return false
     */
    bool HandleFocusReset() override;

    /*!
     * @brief No-op.
     *
     * @param event SFML-Event
     * @return Returns false
     */
    bool Handle(sf::Event event) override;


private:

    /*!
     * @brief Determines the y-coordinate of a certain line
     *
     * @param line number of the line (0...4)
     * @return y-coordinate of the line
     */
    float LineToY(int line) const;

    /*!
     * @brief Sets a line with given name and score
     *
     * @param line number of the line to set (0...4)
     * @param name name of the player
     * @param score score value to display (e.g. victories, time, etc.)
     */
    void SetLine(int line, const std::string& name, const std::string& score);

    /*!
     * @brief Sets the headline of the displayed score type
     *
     * @param headline headline as a string of the displayed score type
     */
    void SetHeadline(const std::string& headline);

    /*!
     * @brief x-coordinate of the scoreboard (upper-left corner)
     */
    float m_X;

    /*!
     * @brief y-coordinate of the scoreboard (upper-left corner)
     */
    float m_Y;

    /*!
     * @brief total width of the scoreboard
     */
    float m_Width;

    /*!
     * @brief SFML-Text: graphical representation of the headline for the current scoreboard
     */
    sf::Text m_HeadlineShape;

    /*!
     * @brief array of SFML-Text elements with graphical representations for the strings "1." to "5."
     */
    sf::Text m_PlacingShapes[5];

    /*!
     * @brief array of SFML-Text elements with graphical representations for the top 5 player names
     */
    sf::Text m_NameShapes[5];

    /*!
     * @brief array of SFML-Text elements with graphical representations for the top 5 scores
     */
    sf::Text m_ScoreShapes[5];

    /*!
     * @brief SFML-Font: font in which the texts and headline will be displayed
     */
    sf::Font m_Font;


};
