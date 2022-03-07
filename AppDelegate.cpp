//
// Created by Brendan Berg on 07.03.22.
//

#include "AppDelegate.hpp"

#include <iostream>


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


void AppDelegate::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
    if (m_Window != nullptr)
    {
        m_Window->close();
    }
    m_Window = std::make_shared<sf::Window>(sf::VideoMode(width, height), title);
}


void AppDelegate::RegisterModel()
{

}


void AppDelegate::RegisterView()
{

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

    sf::Event event;
    while (m_Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_Window->close();
        }
    }

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


void AppDelegate::Delete()
{
    delete instance;
}
