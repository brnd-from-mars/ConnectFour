//
// Created by Brendan Berg on 07.03.22.
//

#include "AppDelegate.hpp"

#include <iostream>

#include "BaseView.hpp"


AppDelegate* AppDelegate::instance = nullptr;


AppDelegate::~AppDelegate()
{
    if (m_Window != nullptr && m_Window->isOpen())
    {
        m_Window->close();
    }
    std::clog << "AppDelegate destructed" << std::endl;
}


AppDelegate* AppDelegate::Get()
{
    if (instance == nullptr)
    {
        instance = new AppDelegate;
    }
    return instance;
}


void AppDelegate::Delete()
{
    delete instance;
}


void AppDelegate::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
    if (m_Window != nullptr)
    {
        m_Window->close();
    }
    m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height),
                                                  title,
                                                  sf::Style::Titlebar | sf::Style::Close);
}


std::shared_ptr<sf::RenderWindow> AppDelegate::GetWindow()
{
    return m_Window;
}


void AppDelegate::RegisterModel()
{

}


void AppDelegate::RegisterView(const std::shared_ptr<BaseView>& view)
{
    m_ViewContainer.push_back(view);
}


void AppDelegate::RegisterController()
{

}


bool AppDelegate::Update()
{
    if (m_Window == nullptr)
    {
        throw std::runtime_error("AppDelegate Update was called before SetWindow");
    }

    m_Window->clear(sf::Color(41, 49, 50));

    auto event = sf::Event();
    while (m_Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_Window->close();
        }
    }

    for (auto& wView : m_ViewContainer)
    {
        if (auto view = wView.lock())
        {
            view->Draw();
        }
    }

    m_Window->display();
    m_Window->setFramerateLimit(30);
    return m_Window->isOpen();
}


AppDelegate::AppDelegate()
{
    if (instance != nullptr)
    {
        throw std::runtime_error("Singleton AppDelegate was constructed multiple times");
    }

    std::clog << "AppDelegate constructed" << std::endl;
}
