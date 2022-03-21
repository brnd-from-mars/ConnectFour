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


AppDelegate* AppDelegate::m_Instance = nullptr;


AppDelegate::AppDelegate()
{
    if (m_Instance != nullptr)
    {
        // singleton implementation does not guarantee single instance creation (e.g. in multi-threading)
        // -> throw error
        throw std::runtime_error("Singleton AppDelegate was constructed multiple times");
    }
    srand(static_cast<unsigned int>(time(nullptr))); // initialize random number generator as soon as app starts
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
    if (m_Instance == nullptr)
    {
        m_Instance = new AppDelegate;
    }
    return m_Instance;
}


void AppDelegate::Delete()
{
    delete m_Instance;
}


void AppDelegate::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
    if (m_Window != nullptr)
    {
        m_Window->close();
    }
    m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title,
                                                  sf::Style::Titlebar | sf::Style::Close);
}


std::shared_ptr<sf::RenderWindow> AppDelegate::GetWindow()
{
    return m_Window;
}


void AppDelegate::SetBackgroundColor(const sf::Color& backgroundColor)
{
    m_BackgroundColor = backgroundColor;
}


void AppDelegate::SetFrameRate(int frameRate)
{
    m_FrameRate = frameRate;
}


void AppDelegate::RegisterModel(const std::shared_ptr<BaseModel>& model)
{
    m_ModelContainer.push_back(model);
}


void AppDelegate::RegisterView(const std::shared_ptr<BaseView>& view)
{
    auto layer = view->GetLayer();
    // find position to insert view in container according to the layers
    // -> drawing all elements from begin to end will automatically draw views on lower layers first
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
    // function is not static to ensure that srand has been called before
    return rand();
}


bool AppDelegate::Update()
{
    if (m_Window == nullptr)
    {
        // throw error as most MVC elements require an existing window in AppDelegate
        throw std::runtime_error("AppDelegate Update was called before SetWindow");
    }

    m_Window->clear(m_BackgroundColor);

    EventPush();

    UpdateModels();
    UpdateControllers();
    DrawViews();

    m_Window->display();
    m_Window->setFramerateLimit(m_FrameRate);

    return m_Window->isOpen();
}


void AppDelegate::EventPush()
{
    auto event = sf::Event();
    while (m_Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_Window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            // if the user clicks somewhere, the focus will likely be shifted to something else or nothing at all
            // -> focus reset required
            // -> if an element is clicked while it is in focus, the focus will be reestablished in the next loop
            for (auto& wView : m_ViewContainer)
            {
                if (auto view = wView.lock())
                {
                    view->HandleFocusReset();
                }
            }
        }

        // iterate through all views from the top to bottom layer and push event
        // break as soon as the first view has completely handled the event
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
}


void AppDelegate::UpdateModels()
{
    auto it = m_ModelContainer.begin();
    while (it != m_ModelContainer.end())
    {
        auto current = it++;
        if (auto model = current->lock())
        {
            model->Update();
        }
        else
        {
            m_ModelContainer.erase(current);
        }
    }
}


void AppDelegate::DrawViews()
{
    auto it = m_ViewContainer.begin();
    while (it != m_ViewContainer.end())
    {
        auto current = it++;
        if (auto view = current->lock())
        {
            view->Draw();
        }
        else
        {
            m_ViewContainer.erase(current);
        }
    }
}


void AppDelegate::UpdateControllers()
{
    auto it = m_ControllerContainer.begin();
    while (it != m_ControllerContainer.end())
    {
        auto current = it++;
        if (auto controller = current->lock())
        {
            controller->Update();
        }
        else
        {
            m_ControllerContainer.erase(current);
        }
    }
}
