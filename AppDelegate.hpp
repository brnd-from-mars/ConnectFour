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
 * \class AppDelegate singleton class handles the creation of the SFML window as well as event pushing and updates in
 * the game loop.
 */
class AppDelegate
{

private:

    AppDelegate();


public:

    AppDelegate(const AppDelegate&) = delete;
    virtual ~AppDelegate();
    static AppDelegate* Get();
    static void Delete();

    void SetWindow(unsigned int width, unsigned int height, const std::string& title);
    std::shared_ptr<sf::RenderWindow> GetWindow();
    void SetBackgroundColor(const sf::Color& backgroundColor);
    void SetFrameRate(int frameRate);

    void RegisterModel(const std::shared_ptr<BaseModel>& model);
    void RegisterView(const std::shared_ptr<BaseView>& view);
    void RegisterController(const std::shared_ptr<BaseController>& controller);

    int GetRandomNumber();

    bool Update();


private:

    void EventPush();
    void UpdateModels();
    void UpdateViews();
    void UpdateControllers();

    static AppDelegate* instance;

    std::shared_ptr<sf::RenderWindow> m_Window;
    sf::Color m_BackgroundColor = sf::Color(0, 0, 0);
    int m_FrameRate = 60;

    std::list<std::weak_ptr<BaseModel>> m_ModelContainer;
    std::list<std::weak_ptr<BaseView>> m_ViewContainer;
    std::list<std::weak_ptr<BaseController>> m_ControllerContainer;


};
