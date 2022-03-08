#include <string>

#include "AppDelegate.hpp"
#include "BaseView.hpp"


class ChipView : public BaseView
{

public:

    explicit ChipView(float centerX, sf::Color color, int layer)
        : m_Circle(100)
    {
        m_Circle.setPosition(centerX-100, 200);
        m_Circle.setFillColor(color);
        m_Layer = layer;
    }

    void Draw() override
    {
        AppDelegate::Get()->GetWindow()->draw(m_Circle);
    }


private:

    sf::CircleShape m_Circle;


};


int main()
{
    AppDelegate::Get()->SetWindow(2560, 1440, "Four Wins!");

    auto chip1 = std::make_shared<ChipView>(200.0f, sf::Color(84, 122, 165), 1);
    auto chip2 = std::make_shared<ChipView>(300.0f, sf::Color(204, 68, 75), 2);

    AppDelegate::Get()->RegisterView(chip1);
    AppDelegate::Get()->RegisterView(chip2);

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
