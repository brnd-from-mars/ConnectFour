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


class TextFieldController : public BaseController
{
    friend TextFieldModel;
    friend TextFieldView;


public:

    static std::shared_ptr<TextFieldController> MakeTextField(float x, float y, float width,
                                                              const std::string& placeholder, sf::Color highlightColor);

    TextFieldController(float x, float y, float width, const std::string& placeholder, sf::Color highlightColor);

    void Update() override;

    void HandleTextEntry(char character);

    void HandleBackspaceKeyPress();

    void HandleEnterKeyPress();

    void RegisterEnterKeyPressCallback(const std::function<void()>& callback);

    void SetHighlightColor(sf::Color highlightColor);

    std::string GetText() const;

    void UpdateView();


private:

    std::shared_ptr<TextFieldModel> m_TextFieldModel;
    std::shared_ptr<TextFieldView> m_TextFieldView;

    std::optional<std::function<void()>> m_EnterKeyPressCallback = std::nullopt;


};
