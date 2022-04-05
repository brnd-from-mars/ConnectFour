//
// Created by Florian Wolff on 10.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"


/*!
 * @brief TextView displays a text with a given size and color on the screen.
 */
class TextView : public BaseView
{

public:

    /*!
     * @brief Static factory function creates a new text.
     *
     * @param x x-coordinate of the text on the screen
     * @param y y-coordinate of the text on the screen
     * @param size font size
     * @param font font in which the text will be displayed
     * @param text text as a string to display
     * @param color color of the displayed text
     * @param layer layer of the text
     * @return shared pointer to the new TextView
     */
    static std::shared_ptr<TextView> MakeText(float x, float y, unsigned int size, const std::string& font,
                                              const std::string& text, sf::Color color, int layer = 0);

    /*!
     * @brief Constructor loads the font and initializes all SFML elements.
     *
     * @param x x-coordinate of the text on the screen
     * @param y y-coordinate of the text on the screen
     * @param size font size
     * @param font font in which the text will be displayed
     * @param text text as a string to display
     * @param color color of the displayed text
     * @param layer layer of the text
     */
    TextView(float x, float y, unsigned int size, const std::string& font,
             const std::string& text, sf::Color color, int layer);

    /*!
     * @brief Draws the text to the RenderWindow in the AppDelegate.
     */
    void Draw() override;

    /*!
     * @brief Sets the text as a string that will be displayed.
     *
     * @param text text as a string to display
     */
    void SetText(const std::string& text);

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
     * @return false
     */
    bool Handle(sf::Event event) override;


private:

    /*!
     * @brief SFML-Text: graphical representation of the text that will be displayed
     */
    sf::Text m_TextShape;

    /*!
     * @brief SFML-Font: font in which the text will be displayed
     */
    sf::Font m_Font;


};
