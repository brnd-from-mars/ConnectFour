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


/*!
 * @brief Private constructor for the AppDelegate singleton.
 *
 * Private constructor for the AppDelegate singleton checks whether the singleton instance already exists or not.
 * Provides time based seed for random number generator.
 *
 * @throw std::runtime_error in case instance already exists
 */
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


/*!
 * @brief Destructor for AppDelegate singleton closes associated SFML RenderWindow.
 */
AppDelegate::~AppDelegate()
{
    if (m_Window != nullptr && m_Window->isOpen())
    {
        m_Window->close();
    }
    std::clog << "AppDelegate destructed" << std::endl;
}


/*!
 * @brief Static function returns pointer to singleton instance and constructs it if necessary.
 *
 * @return pointer to AppDelegate singleton instance
 */
AppDelegate* AppDelegate::Get()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new AppDelegate;
    }
    return m_Instance;
}


/*!
 * @brief Static function deletes singleton instance. HAS to be called at the end of the program.
 */
void AppDelegate::Delete()
{
    delete m_Instance;
}


/*!
 * @brief Creates a new SFML RenderWindow with the provided configuration. Closes the previous instantiated window in
 * case one exists.
 *
 * @param width width of the window
 * @param height height of the window
 * @param title title of the window
 */
void AppDelegate::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
    if (m_Window != nullptr)
    {
        m_Window->close();
    }
    m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title,
                                                  sf::Style::Titlebar | sf::Style::Close);
}


/*!
 * @return Shared pointer to associated SFML RenderWindow
 */
std::shared_ptr<sf::RenderWindow> AppDelegate::GetWindow()
{
    return m_Window;
}


/*!
 * @brief Sets background color of associated SFML RenderWindow
 *
 * @param backgroundColor SFML background color
 */
void AppDelegate::SetBackgroundColor(const sf::Color& backgroundColor)
{
    m_BackgroundColor = backgroundColor;
}


/*!
 * @brief Sets frameRate for application updates
 *
 * @param frameRate frame rate
 */
void AppDelegate::SetFrameRate(int frameRate)
{
    m_FrameRate = frameRate;
}


/*!
 * @brief Adds a new BaseModel derivative to the update handling list. AppDelegate will hold a weak pointer.
 *
 * @param model shared pointer to the model
 */
void AppDelegate::RegisterModel(const std::shared_ptr<BaseModel>& model)
{
    m_ModelContainer.push_back(model);
}


/*!
 * @brief Add a new BaseView derivative to the draw handling list while maintaining the layer order. AppDelegate will
 * hold a weak pointer.
 *
 * @param view shared pointer to the view
 */
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


/*!
 * Adds a new BaseController derivative to the update handling list. AppDelegate will hold a weak pointer.
 *
 * @param controller shared pointer to the controller
 */
void AppDelegate::RegisterController(const std::shared_ptr<BaseController>& controller)
{
    m_ControllerContainer.push_back(controller);
}

/*!
 * @return random integer
 */
int AppDelegate::GetRandomNumber()
{
    // function is not static to ensure that srand has been called before
    return rand();
}


/*!
 * Application update handler pushes SFML events and updates MVC elements.
 *
 * @return Application still running
 */
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
    UpdateViews();

    m_Window->display();
    m_Window->setFramerateLimit(m_FrameRate);

    return m_Window->isOpen();
}


/*!
 * @brief Pushes events to all views starting from the top layer until they are handled successfully.
 *
 * Pushes events to all views starting from the top layer until they are handled successfully. Before a
 * MouseButtonPressed event is sent, the FocusReset event will be send.
 */
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


/*!
 * @brief Updates all models in the model update list and erases invalid weak pointers to deleted models.
 */
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


/*!
 * Draws all views in the view draw list and erases invalid weak pointers to deleted views.
 */
void AppDelegate::UpdateViews()
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


/*!
 * Updates all controllers in the controller update list and erases invalid weak pointers to deleted controllers.
 */
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
