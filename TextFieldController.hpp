//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>
#include <optional>
#include <functional>

#include <SFML/Graphics.hpp>

#include "BaseController.hpp"

class TextFieldModel;
class TextFieldView;


/*!
 * @brief TextFieldController class represents a text field in which a user can enter text.
 */
class TextFieldController : public BaseController
{
    friend TextFieldModel;
    friend TextFieldView;


public:

    /*!
     * @brief Static factory function creates a new text field and sets references between the MVC elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param placeholder placeholder string to display when no text is entered
     * @param highlightColor color for the outline and text to use while the text field is in focus
     * @return shared pointer to the new TextFieldController
     */
    static std::shared_ptr<TextFieldController> MakeTextField(float x, float y, float width,
                                                              const std::string& placeholder, sf::Color highlightColor);

    /*!
     * @brief Constructor creates associated TextFieldModel and TextFieldView
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param placeholder placeholder string to display when no text is entered
     * @param highlightColor color for the outline and text to use while the text field is in focus
     */
    TextFieldController(float x, float y, float width, const std::string& placeholder, sf::Color highlightColor);

    /*!
     * @brief No-op.
     */
    void Update() override;

    /*!
     * @brief Registers a given function pointer as the callback for a enter key press event
     *
     * @param callback void() function pointer to the event listener
     */
    void RegisterEnterKeyPressCallback(const std::function<void()>& callback);

    /*!
     * @brief Sets the highlight color for the text field.
     *
     * @param highlightColor highlight color
     */
    void SetHighlightColor(sf::Color highlightColor);

    /*!
     * @brief Overrides the text entered into the text field.
     *
     * @param text text string
     */
    void SetText(const std::string& text);

    /*!
     * @brief Gets the currently entered text
     *
     * @return entered text string
     */
    std::string GetText() const;


private:

    /*!
     * @brief Handles text entry events by pushing them to the model and adding the character.
     */
    void HandleTextEntry(char character);

    /*!
     * @brief Handles backspace key press events by pushing them to the model and deleting a character.
     */
    void HandleBackspaceKeyPress();

    /*!
     * @brief Handles enter key press events by pushing them to the model.
     */
    void HandleEnterKeyPress();

    /*!
     * @brief Updates the view after changes to the model.
     */
    void UpdateView();

    /*!
     * shared pointer (ownership) to the TextFieldModel
     */
    std::shared_ptr<TextFieldModel> m_TextFieldModel;

    /*!
     * shared pointer (ownership) to the TextFieldView
     */
    std::shared_ptr<TextFieldView> m_TextFieldView;

    /*!
     * @brief function pointer for the enter key press event callback
     */
    std::optional<std::function<void()>> m_EnterKeyPressCallback = std::nullopt;


};
