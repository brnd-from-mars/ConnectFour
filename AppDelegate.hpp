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


namespace ColorPalette
{
    const sf::Color Basestar = sf::Color(12, 20, 31);
    const sf::Color BasestarDark = sf::Color(8, 13, 21);

    const sf::Color Orange = sf::Color(233, 126, 22);
    const sf::Color Cyan = sf::Color(0, 255, 255);
    const sf::Color Pane = sf::Color(230,255,255);
    const sf::Color SweetYellow = sf::Color(255,230,77);
    const sf::Color Gray = sf::Color(85,85,85);
    const sf::Color DarkBlue = sf::Color(6,36,116);
    const sf::Color PrussianBlue = sf::Color(0,49,83);
    const sf::Color Pred = sf::Color(255, 0, 85);

}


class AppDelegate
{

private:

    AppDelegate();

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

    static AppDelegate* instance;

    std::shared_ptr<sf::RenderWindow> m_Window;

    std::list<std::weak_ptr<BaseModel>> m_ModelContainer;
    std::list<std::weak_ptr<BaseView>> m_ViewContainer;
    std::list<std::weak_ptr<BaseController>> m_ControllerContainer;


};
