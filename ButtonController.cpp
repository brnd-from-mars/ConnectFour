//
// Created by Brendan Berg on 12.03.22.
//

#include "ButtonView.hpp"
#include "ButtonController.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<ButtonController> ButtonController::MakeButton(float x, float y, float width, const std::string& text,
                                                               sf::Color defaultColor, sf::Color highlightColor)
{
    auto controller = std::make_shared<ButtonController>(x, y, width, text, defaultColor, highlightColor);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_ButtonView->m_ButtonController = controller;

    return controller;
}


ButtonController::ButtonController(float x, float y, float width, const std::string& text,
                                   sf::Color defaultColor, sf::Color highlightColor)
{
    m_ButtonView = std::make_shared<ButtonView>(x, y, width, text, defaultColor, highlightColor);
    AppDelegate::Get()->RegisterView(m_ButtonView);
}


void ButtonController::Update()
{ }


void ButtonController::RegisterMousePressCallback(const std::function<void()>& callback)
{
    m_MousePressCallback = callback;
}


void ButtonController::HandleMousePress()
{
    // if callback registered
    if (m_MousePressCallback)
    {
        // extract std::function pointer from std::optional
        auto callback = m_MousePressCallback.value();
        // call function
        callback();
    }
}
