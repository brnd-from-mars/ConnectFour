//
// Created by Brendan Berg on 07.03.22.
//

#ifndef FOURWINS_APPDELEGATE_HPP
#define FOURWINS_APPDELEGATE_HPP

#include <memory>
#include <string>

#include <SFML/graphics.hpp>


class AppDelegate
{

public:

    ~AppDelegate();

    static AppDelegate* Get();

    void SetWindow(unsigned int width, unsigned int height, const std::string& title);

    void RegisterModel();

    void RegisterView();

    void RegisterController();

    bool Update();

    void Delete();


private:

    AppDelegate();

    static AppDelegate* instance;

    std::shared_ptr<sf::Window> m_Window;


};


#endif //FOURWINS_APPDELEGATE_HPP
