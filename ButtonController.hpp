//
// Created by Brendan Berg on 12.03.22.
//

#pragma once

#include <memory>
//#include <optional>
//#include <functional>

#include <SFML/Graphics.hpp>

#include "BaseController.hpp"

#include "AppDelegate.hpp"

class ButtonView;


class ButtonController : public BaseController
{
    friend ButtonView;


public:

    static std::shared_ptr<ButtonController> MakeButton(float x, float y, float width, const std::string& text,
                                                        sf::Color defaultColor,
                                                        sf::Color highlightColor = ColorPalette::BasestarDark);

    ButtonController(float x, float y, float width, const std::string& text,
                     sf::Color defaultColor, sf::Color highlightColor);

    void Update() override;

    void HandleMousePress();

    //void RegisterMousePressCallback(const std::function<void()>& callback);


private:

    std::shared_ptr<ButtonView> m_ButtonView;

    //std::optional<std::function<void()>> m_MousePressCallback = std::nullopt;


};
