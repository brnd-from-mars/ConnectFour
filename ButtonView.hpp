//
// Created by Florian Wolff on 10.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ButtonController;

/*!
* @brief ButtonView class represents a clickable button on the screen
*/
class ButtonView : public BaseView
{
    friend ButtonController;


public:

    /*!
     * @brief Constructor creates a new button
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param text text inside the button
     * @param defaultColor default display color for the button
     * @param highlightColor highlight (pressed) color for the button
     */
    ButtonView(float x, float y, float width, const std::string& text,
               sf::Color defaultColor, sf::Color highlightColor);

    /*!
    *@brief Adresses the AppDelegate and draws the button on the screen
    */
    void Draw() override;

    /*!
   * @brief No-op.
   *
   * @return Returns false
   */
    bool HandleFocusReset() override;

    /*!
   * @brief Checks if a mouseclick event is within its boundarys, sets variables and returnvalue accordingly and reports back
   * to the controller
   *
   * @param event Event which is given to handle
   * @return Returns if this button was clicked or not
   */
    bool Handle(sf::Event event) override;


private:

    /*!
   * @brief Updates the view and highlights the button if it was pressed
   */
    void UpdateView();

    /*!
   * @brief Weak pointer to the associated controller
   */
    std::weak_ptr<ButtonController> m_ButtonController;

    /*!
   * @brief Shape of the button itself
   */
    sf::RectangleShape m_ButtonField;

    /*!
   * @brief Shape of the text displayed on the button
   */
    sf::Text m_TextShape;

    /*!
   * @brief Font in which the text is displayed
   */
    sf::Font m_Font;

    /*!
   * @brief Default color of the outline
   */
    sf::Color m_DefaultColor;

    /*!
    * @brief Color of the outline if the button was pressed
    */
    sf::Color m_HighlightColor;

    /*!
    * @brief Variable weather the button was pressed
    */
    bool m_Pressed = false;


};
