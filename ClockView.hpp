//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ClockController;


/*!
 * @brief ClockView displays the current time on the screen.
 */
class ClockView : public BaseView
{
    friend ClockController;


public:

    /*!
     * @brief Constructor loads the font and initializes all SFML elements. The initial text will be set to
     * "T+00:00:000"
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param color text color
     */
    ClockView(float x, float y, sf::Color color);

    /*!
     * @brief Draws the clock to the screen.
     */
    void Draw() override;

    /*!
     * @brief No-op.
     * @return false
     */
    bool HandleFocusReset() override;

    /*!
     * @brief No-op.
     * @return false
     */
    bool Handle(sf::Event event) override;


private:

    /*!
     * @brief Updates the text displayed on screen
     *
     * @param minutes number of minutes that passed
     * @param seconds number of seconds that passed since the last minute ended
     * @param millis number of milliseconds that passed since the last seconds ended
     */
    void SetTime(int minutes, int seconds, int millis);


    /*!
     * @brief SFML-Font: Standard
     */
    sf::Font m_Font;

    /*!
     * @brief SFML-Text: Prefix for the clock text: "T+"
     */
    sf::Text m_PrefixTextShape;

    /*!
     * @brief SFML-Text: Minute clock text: "00"
     */
    sf::Text m_MinutesTextShape;

    /*!
     * @brief SFML-Text: First separating dots: ":"
     */
    sf::Text m_Dots1TextShape;

    /*!
     * @brief SFML-Text: Seconds clock text: "00"
     */
    sf::Text m_SecondsTextShape;

    /*!
     * @brief SFML-Text: Second separating dots: ":"
     */
    sf::Text m_Dots2TextShape;

    /*!
     * @brief SFML-Text: Milliseconds clock text: "000"
     */
    sf::Text m_MillisTextShape;

    /*!
     * @brief dots will be visible in the first half of every second while the clock is running
     */
    bool m_DotsVisible = true;

    /*!
     * @brief dots will be visible continuously after the clock was stopped
     */
    bool m_ForceDotsVisible = false;


};
