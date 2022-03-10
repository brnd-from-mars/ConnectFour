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

    static std::shared_ptr<TextFieldController> MakeTextField(float x, float y, float width);

    TextFieldController(float x, float y, float width);

    void Update() override;

    void HandleTextEntry(char character); // TODO: make private

    void HandleDeleteKeyPress(); // TODO: make private

    void UpdateView(); // TODO: make private


private:

    std::shared_ptr<TextFieldModel> m_TextFieldModel;
    std::shared_ptr<TextFieldView> m_TextFieldView;


};
