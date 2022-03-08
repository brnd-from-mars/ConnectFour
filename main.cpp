#include <string>
#include <cmath>
#include <iostream>

#include "AppDelegate.hpp"
#include "BaseModel.hpp"
#include "BaseView.hpp"
#include "BaseController.hpp"

class ChipModel;
class ChipView;
class ChipController;


class ChipModel : public BaseModel
{
friend ChipView;
friend ChipController;

public:

    ChipModel(int player, int column, int row)
        : m_Player(player), m_Column(column), m_Row(row)
    {

    }

    void Update() override
    {

    }


private:

    std::weak_ptr<ChipController> m_ChipController;

    int m_Player;

    int m_Column;

    int m_Row;


};


class ChipView : public BaseView
{
friend ChipModel;
friend ChipController;

public:

    explicit ChipView()
        : m_Circle(m_Radius)
    {
        m_Layer = 2;
    }

    void SetPosition(float x, float y)
    {
        m_Circle.setPosition(x - m_Radius, y - m_Radius);
    }

    void SetFillColor(sf::Color color)
    {
        m_Circle.setFillColor(color);
    }

    void Draw() override
    {
        AppDelegate::Get()->GetWindow()->draw(m_Circle);
    }

    bool ResetFocus() override
    {
        return false;
    }

    bool Handle(sf::Event event) override
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // TODO: check if left click
            auto dx = event.mouseButton.x - (m_Circle.getPosition().x + m_Radius);
            auto dy = event.mouseButton.y - (m_Circle.getPosition().y + m_Radius);
            if (sqrt(dx * dx + dy * dy) <= m_Radius)
            {
                return true;
            }
        }

        return false;
    }


private:

    std::weak_ptr<ChipController> m_ChipController;

    sf::CircleShape m_Circle;

    sf::CircleShape m_Ring;

    static constexpr float m_Radius = 48.0f;


};


class ChipController : public BaseController
{
friend ChipModel;
friend ChipView;

public:

    static std::shared_ptr<ChipController> MakeChip(int player, int column, int row)
    {
        auto controller = std::make_shared<ChipController>(player, column, row);
        AppDelegate::Get()->RegisterController(controller);

        controller->m_ChipModel->m_ChipController = controller;
        controller->m_ChipView->m_ChipController = controller;

        return controller;
    }

    ChipController(int player, int column, int row)
    {
        m_ChipModel = std::make_shared<ChipModel>(player, column, row);
        AppDelegate::Get()->RegisterModel(m_ChipModel);

        m_ChipView = std::make_shared<ChipView>();
        AppDelegate::Get()->RegisterView(m_ChipView);

        UpdateView();
    }

    void UpdateView()
    {
        m_ChipView->SetPosition(100.0f * m_ChipModel->m_Column, 100.0f * (14 - m_ChipModel->m_Row));
        m_ChipView->SetFillColor(m_PlayerColors[m_ChipModel->m_Player - 1]);
    }

    void Update() override
    {

    }


private:

    std::shared_ptr<ChipModel> m_ChipModel;
    std::shared_ptr<ChipView> m_ChipView;

    static sf::Color m_PlayerColors[2];

};

sf::Color ChipController::m_PlayerColors[2] = {sf::Color(84, 122, 165), sf::Color(204, 68, 75)};


int main()
{
    AppDelegate::Get()->SetWindow(2560, 1440, "Four Wins!");

    auto chip1 = ChipController::MakeChip(1, 0, 0);
    auto chip2 = ChipController::MakeChip(1, 1, 0);
    auto chip3 = ChipController::MakeChip(2, 1, 1);

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
