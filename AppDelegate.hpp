//
// Created by Brendan Berg on 07.03.22.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class BaseView;


class AppDelegate
{

public:

    ~AppDelegate();

    static AppDelegate* Get();

    static void Delete();

    void SetWindow(unsigned int width, unsigned int height, const std::string& title);

    std::shared_ptr<sf::RenderWindow> GetWindow();

    void RegisterModel();

    void RegisterView(const std::shared_ptr<BaseView>& view);

    void RegisterController();

    bool Update();


private:

    AppDelegate();

    static AppDelegate* instance;

    std::shared_ptr<sf::RenderWindow> m_Window;

    std::vector<std::weak_ptr<BaseView>> m_ViewContainer;


};
