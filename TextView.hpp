//
// Created by Florian Wolff on 10.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

/*!
* @brief TextView represents a simple displayed text
*/
class TextView : public BaseView
{

public:

    /*!
    * @brief Static factory function creates a new text
    *
    * @param x X-coordinate of the text on the screen
    * @param y Y-coordinate of the text on the screen
    * @param size Size of the text in pixels
    * @param font Font in which the text should be displayed
    * @param text Text to display
    * @param color Color of the displayed text
    * @param layer Layer of the text
    * @return Shared pointer to the TextView
    */
    static std::shared_ptr<TextView> MakeText(float x, float y, unsigned int size, const std::string& font,
                                              const std::string& text, sf::Color color, int layer = 0);

    /*!
    * @brief Constructor creates the associated TextView
    *
    * @param x X-coordinate of the text on the screen
    * @param y Y-coordinate of the text on the screen
    * @param size Size of the text in pixels
    * @param font Font in which the text should be displayed
    * @param text Text to display
    * @param color Color of the displayed text
    * @param layer Layer of the text
    */
    TextView(float x, float y, unsigned int size, const std::string& font,
             const std::string& text, sf::Color color, int layer);

    /*!
    *@brief Adresses the AppDelegate and draws the text on the screen
    */
    void Draw() override;

    /*!
    *@brief Sets the text which should be displayed
    * 
    * @param text String with the text to diplay
    */
    void SetText(const std::string& text);

    /*!
    * @brief No-op.
    *
    * @return Returns false
    */
    bool HandleFocusReset() override;

    /*!
    * @brief No-op.
    *
    * @param event Event to handle
    * @return Returns false
    */
    bool Handle(sf::Event event) override;


private:

    /*!
   * @brief Shape of the text which should be displayed
   */
    sf::Text m_TextShape;

    /*!
   * @brief Font in which the text is displayed
   */
    sf::Font m_Font;


};
