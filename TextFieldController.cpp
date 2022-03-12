//
// Created by Brendan Berg on 09.03.22.
//

#include <iostream>

#include "TextFieldController.hpp"

#include "AppDelegate.hpp"

#include "TextFieldModel.hpp"
#include "TextFieldView.hpp"


std::shared_ptr<TextFieldController> TextFieldController::MakeTextField(float x, float y, float width,
                                                                        const std::string& placeholder,
                                                                        sf::Color highlightColor)
{
    auto controller = std::make_shared<TextFieldController>(x, y, width, placeholder, highlightColor);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_TextFieldView->m_TextFieldController = controller;

    return controller;
}


TextFieldController::TextFieldController(float x, float y, float width,
                                         const std::string& placeholder, sf::Color highlightColor)
{
    m_TextFieldModel = std::make_shared<TextFieldModel>();
    AppDelegate::Get()->RegisterModel(m_TextFieldModel);

    m_TextFieldView = std::make_shared<TextFieldView>(x, y, width, placeholder, highlightColor);
    AppDelegate::Get()->RegisterView(m_TextFieldView);
}


void TextFieldController::Update()
{ }


void TextFieldController::HandleTextEntry(char character)
{
    m_TextFieldModel->AddCharacter(character);
    UpdateView();
}


void TextFieldController::HandleBackspaceKeyPress()
{
    m_TextFieldModel->DeleteCharacter();
    UpdateView();
}


void TextFieldController::HandleEnterKeyPress()
{
    if (m_EnterKeyPressCallback)
    {
        auto callback = m_EnterKeyPressCallback.value();
        callback();
    }
}


void TextFieldController::RegisterEnterKeyPressCallback(const std::function<void()>& callback)
{
    m_EnterKeyPressCallback = callback;
}


std::string TextFieldController::GetText() const
{
    return m_TextFieldModel->m_Text;
}


void TextFieldController::UpdateView()
{
    m_TextFieldView->SetText(m_TextFieldModel->m_Text);
}
