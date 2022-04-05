//
// Created by Florian Wolff on 09.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class TextFieldController;

/*!
* @brief TextFieldView represents a text field in which text can be entered and displayed
*/
class TextFieldView : public BaseView
{
    friend TextFieldController;


public:

    /*!
     * @brief Constructor creates a new text field
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param placeholder Placeholder string to display when no text is entered
     * @param highlightColor Outline color when the text field is selected
     */
    TextFieldView(float x, float y, float width, const std::string& placeholder, sf::Color highlightColor);

    /*!
    *@brief Adresses the AppDelegate and draws the text field
    */
    void Draw() override;

    /*!
    *@brief Checks if the focus variable is false and changes the outline accordingly
    * 
    * @return returns true
    */
    bool HandleFocusReset() override;

    /*!
    *@brief Dependent on the event type the outline color changes if selected or deselected, displays a changed text
    * or passes on the confirmation of the input
    * 
    * @param event Event given to handle
    * @return Returns if it has done something due to the event
    */
    bool Handle(sf::Event event) override;

    /*!
     *@brief Sets the highlight color to display the entered thext in this color
     *
     * @param highlightColor Color in which the text should be highlighted
     */
    void SetHighlightColor(sf::Color highlightColor);

    /*!
     *@brief Sets the text which should be displayed
     *
     * @param text Text which should be displayed
     */
    void SetText(const std::string& text);


private:

    /*!
     *@brief Sets the outline color of the textfield according to its focus status
     */
    void UpdateView();

    /*!
   * @brief Weak pointer to the associated controller
   */
    std::weak_ptr<TextFieldController> m_TextFieldController;

    /*!
   * @brief Shape of the textfield without the text
   */
    sf::RectangleShape m_TextField;

    /*!
   * @brief Shape of the text displayed in the textfield
   */
    sf::Text m_TextShape;

    /*!
   * @brief Shape the placeholder text if no text was entered
   */
    sf::Text m_PlaceholderShape;

    /*!
   * @brief Font in which the text is displayed
   */
    sf::Font m_Font;

    /*!
   * @brief Color in which entered text is displayed
   */
    sf::Color m_HighlightColor;

    /*!
   * @brief Variable if the textfield is in focus
   */
    bool m_InFocus = false;
};

