//
// Created by Brendan Berg on 07.03.22.
//

#pragma once

#include <memory>
#include <string>
#include <list>

#include <SFML/Graphics.hpp>

class BaseModel; // forward-declaration to avoid cyclic include
class BaseView;
class BaseController;


/*!
 * @brief AppDelegate singleton class handles the creation of the SFML window as well as event pushing and updates in
 * the game loop.
 */
class AppDelegate
{

private:

    /*!
     * @brief Private constructor for the AppDelegate singleton.
     *
     * Private constructor for the AppDelegate singleton checks whether the singleton instance already exists or not.
     * Provides time based seed for random number generator.
     *
     * @throw std::runtime_error in case instance already exists
     */
    AppDelegate();


public:

    /*!
     * @brief Destructor for AppDelegate singleton closes associated SFML RenderWindow.
     */
    virtual ~AppDelegate();

    /*!
     * @brief Static function returns pointer to singleton instance and constructs it if necessary.
     *
     * @return pointer to AppDelegate singleton instance
     */
    static AppDelegate* Get();

    /*
     * @brief Deleted copy constructor
     */
    AppDelegate(const AppDelegate&) = delete;

    /*!
     * @brief Static function deletes singleton instance. HAS to be called at the end of the program.
     */
    static void Delete();

    /*!
     * @brief Creates a new SFML RenderWindow with the provided configuration. Closes the previous instantiated window in
     * case one exists.
     *
     * @param width width of the window
     * @param height height of the window
     * @param title title of the window
     */
    void SetWindow(unsigned int width, unsigned int height, const std::string& title);


    /*!
     * @return Shared pointer to associated SFML RenderWindow
     */
    std::shared_ptr<sf::RenderWindow> GetWindow();


    /*!
     * @brief Sets background color of associated SFML RenderWindow
     *
     * @param backgroundColor SFML background color
     */
    void SetBackgroundColor(const sf::Color& backgroundColor);

    /*!
     * @brief Sets frameRate for application updates
     *
     * @param frameRate frame rate
     */
    void SetFrameRate(int frameRate);


    /*!
     * @brief Adds a new BaseModel derivative to the update handling list. AppDelegate will hold a weak pointer.
     *
     * @param model shared pointer to the model
     */
    void RegisterModel(const std::shared_ptr<BaseModel>& model);


    /*!
     * @brief Add a new BaseView derivative to the draw handling list while maintaining the layer order. AppDelegate will
     * hold a weak pointer.
     *
     * @param view shared pointer to the view
     */
    void RegisterView(const std::shared_ptr<BaseView>& view);


    /*!
     * @brief Adds a new BaseController derivative to the update handling list. AppDelegate will hold a weak pointer.
     *
     * @param controller shared pointer to the controller
     */
    void RegisterController(const std::shared_ptr<BaseController>& controller);


    /*!
     * @return random integer
     */
    int GetRandomNumber();


    /*!
     * @brief Application update handler pushes SFML events and updates MVC elements.
     *
     * @return Application still running
     */
    bool Update();


private:

    /*!
     * @brief Pushes events to all views starting from the top layer until they are handled successfully.
     *
     * Pushes events to all views starting from the top layer until they are handled successfully. Before a
     * MouseButtonPressed event is sent, the FocusReset event will be send.
     */
    void EventPush();

    /*!
     * @brief Updates all models in the model update list and erases invalid weak pointers to deleted models.
     */
    void UpdateModels();

    /*!
     * @brief Draws all views in the view draw list and erases invalid weak pointers to deleted views.
     */
    void UpdateViews();


    /*!
     * @brief Updates all controllers in the controller update list and erases invalid weak pointers to deleted.
     * controllers.
     */
    void UpdateControllers();

    /*!
     * @brief Static pointer to AppDelegate singleton instance
     */
    static AppDelegate* m_Instance;

    /*!
     * @brief Shared pointer to associated SFML RenderWindow
     */
    std::shared_ptr<sf::RenderWindow> m_Window;

    /*!
     * @brief Background color for SFML RenderWindow
     */
    sf::Color m_BackgroundColor = sf::Color(0, 0, 0);

    /*!
     * @brief Application framerate
     */
    int m_FrameRate = 60;

    /*!
     * @brief List of weak pointers to all registered models
     */
    std::list<std::weak_ptr<BaseModel>> m_ModelContainer;

    /*!
     * @brief List of weak pointers to all registered views
     */
    std::list<std::weak_ptr<BaseView>> m_ViewContainer;

    /*!
     * @brief List of weak pointers to all registered controllers
     */
    std::list<std::weak_ptr<BaseController>> m_ControllerContainer;


};
