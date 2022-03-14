//
// Created by Brendan Berg on 07.03.22.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "AppDelegate.hpp"

#include "BaseModel.hpp"
#include "BaseView.hpp"
#include "BaseController.hpp"


AppDelegate* AppDelegate::instance = nullptr;


AppDelegate::AppDelegate()
{
    if (instance != nullptr)
    {
        // singleton implementation does not guarantee single instance creation (e.g. in multi-threading)
        throw std::runtime_error("Singleton AppDelegate was constructed multiple times");
    }
    srand(static_cast<unsigned int>(time(nullptr)));
    std::clog << "AppDelegate constructed" << std::endl;
}


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


void AppDelegate::RegisterModel(const std::shared_ptr<BaseModel>& model)
{
    m_ModelContainer.push_back(model);
}


void AppDelegate::RegisterView(const std::shared_ptr<BaseView>& view)
{
    auto layer = view->GetLayer();
    auto it = std::find_if(m_ViewContainer.begin(),
                           m_ViewContainer.end(),
                           [layer](const std::weak_ptr<BaseView>& wIt) -> bool
                           {
                               if (auto it = wIt.lock())
                               {
                                   return (it->GetLayer() >= layer);
                               }
                               return false;
                           });
    m_ViewContainer.insert(it, view);
}


void AppDelegate::RegisterController(const std::shared_ptr<BaseController>& controller)
{
    m_ControllerContainer.push_back(controller);
}


int AppDelegate::GetRandomNumber()
{
    return rand();
}


bool AppDelegate::Update()
{
    // TODO: add garbage collection

    if (m_Window == nullptr)
    {
        throw std::runtime_error("AppDelegate Update was called before SetWindow");
    }

    m_Window->clear(ColorPalette::Basestar);

    auto event = sf::Event();
    while (m_Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_Window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            for (auto& wView : m_ViewContainer)
            {
                if (auto view = wView.lock())
                {
                    view->HandleFocusReset();
                }
            }
        }

        for (auto wView = m_ViewContainer.rbegin(); wView != m_ViewContainer.rend(); ++wView)
        {
            if (auto view = wView->lock())
            {
                if (view->Handle(event))
                {
                    break;
                }
            }
        }
    }

    for (auto& wModel : m_ModelContainer)
    {
        if (auto model = wModel.lock())
        {
            model->Update();
        }
    }

    for (auto& wController : m_ControllerContainer)
    {
        if (auto controller = wController.lock())
        {
            controller->Update();
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
