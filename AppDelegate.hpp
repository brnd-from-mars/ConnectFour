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


class AppDelegate
{

public:

    // TODO: disallow copy

    virtual ~AppDelegate();

    static AppDelegate* Get();

    static void Delete();

    void SetWindow(unsigned int width, unsigned int height, const std::string& title);

    std::shared_ptr<sf::RenderWindow> GetWindow();

    void RegisterModel(const std::shared_ptr<BaseModel>& model);

    void RegisterView(const std::shared_ptr<BaseView>& view);

    void RegisterController(const std::shared_ptr<BaseController>& controller);

    bool Update();


private:

    AppDelegate();

    static AppDelegate* instance;

    std::shared_ptr<sf::RenderWindow> m_Window;

    std::list<std::weak_ptr<BaseModel>> m_ModelContainer;

    std::list<std::weak_ptr<BaseView>> m_ViewContainer;

    std::list<std::weak_ptr<BaseController>> m_ControllerContainer;


};
