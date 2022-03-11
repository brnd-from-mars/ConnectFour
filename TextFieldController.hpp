//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

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

    void HandleDeleteKeyPress();

    void UpdateView();


private:

    std::shared_ptr<TextFieldModel> m_TextFieldModel;
    std::shared_ptr<TextFieldView> m_TextFieldView;


};
