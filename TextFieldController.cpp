//
// Created by Brendan Berg on 09.03.22.
//

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
{

}


void TextFieldController::HandleTextEntry(char character)
{
    m_TextFieldModel->AddCharacter(character);
    UpdateView();
}


void TextFieldController::HandleDeleteKeyPress()
{
    m_TextFieldModel->DeleteCharacter();
    UpdateView();
}


void TextFieldController::UpdateView()
{
    m_TextFieldView->SetText(m_TextFieldModel->m_Text);
}
