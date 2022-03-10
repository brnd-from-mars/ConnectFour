//
// Created by Brendan Berg on 09.03.22.
//

#include "ChipController.hpp"

#include "AppDelegate.hpp"

#include "ChipModel.hpp"
#include "ChipView.hpp"


std::shared_ptr<ChipController> ChipController::MakeChip(int player, int column, int row)
{
    auto controller = std::make_shared<ChipController>(player, column, row);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_ChipModel->m_ChipController = controller;
    controller->m_ChipView->m_ChipController = controller;

    return controller;
}


ChipController::ChipController(int player, int column, int row)
{
    m_ChipModel = std::make_shared<ChipModel>(player, column, row);
    AppDelegate::Get()->RegisterModel(m_ChipModel);

    m_ChipView = std::make_shared<ChipView>();
    AppDelegate::Get()->RegisterView(m_ChipView);

    UpdateView();
}


void ChipController::Update()
{

}


void ChipController::HandleFocusReset()
{
    m_ChipModel->SetHighlight(false);
    UpdateView();
}


void ChipController::HandleClick()
{
    m_ChipModel->SetHighlight(true);
    UpdateView();
}


void ChipController::UpdateView()
{
    sf::Color playerColors[2] = {sf::Color(84, 122, 165), sf::Color(204, 68, 75)};

    m_ChipView->SetPosition(50.0f + 50.0f * m_ChipModel->m_Column, 50.0f + 50.0f * (9 - m_ChipModel->m_Row));
    m_ChipView->SetFillColor(playerColors[m_ChipModel->m_Player - 1]);
    m_ChipView->EnableRing(m_ChipModel->m_Highlighted);
}
