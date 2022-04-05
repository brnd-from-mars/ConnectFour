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
* @brief ScoreBoardView represents the whole scoreboard without buttons and title
*/
class ScoreBoardView : public BaseView
{
    friend ScoreBoardController;

public:

    /*!
     * @brief Constructor creates the scoreboard
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width of the scoreboard
     */
    ScoreBoardView(float x, float y, float width);

    /*!
    *@brief Adresses the AppDelegate and draws the shapes of the scoreboard on the screen
    */
    void Draw() override;

    /*!
   * @brief No-op.
   *
   * @return Returns false
   */
    bool HandleFocusReset() override;

    /*!
   * @brief No-op.
   *
   * @return Returns false
   */
    bool Handle(sf::Event event) override;


private:

    /*!
   * @brief Function to determine the y-coordinate of a certain line
   *
   * @param line Number of the requested line
   * @return Returns the y-coordinate of the requested line
   */
    float LineToY(int line) const;

    /*!
   * @brief Sets a line with given name and score
   *
   * @param line Number of the line to set
   * @param name Name of the player
   * @param score Scorevalue to display
   */
    void SetLine(int line, const std::string& name, const std::string& score);

    /*!
   * @brief Sets the headline of the displayed scoretype
   *
   * @param headline String of the displayed scoretype
   */
    void SetHeadline(const std::string& headline);

    /*!
   * @brief X-Coordinate of the scoreboard
   */
    float m_X;

    /*!
   * @brief Y-Coordinate of the scoreboard
   */
    float m_Y;

    /*!
   * @brief Total width of the scoreboard
   */
    float m_Width;

    /*!
   * @brief Shape of the headline to display the type of score
   */
    sf::Text m_HeadlineShape;

    /*!
   * @brief Array of shapes to display the placement number
   */
    sf::Text m_PlacingShapes[5];

    /*!
   * @brief Array of shapes to display the player name for each score
   */
    sf::Text m_NameShapes[5];

    /*!
   * @brief Array of shapes to display the score a player achieved
   */
    sf::Text m_ScoreShapes[5];

    /*!
   * @brief Font in which the text is displayed
   */
    sf::Font m_Font;


};
