//
// Created by Brendan Berg on 09.03.22.
//

#include <iostream>

#include "ChipController.hpp"

#include "AppDelegate.hpp"

#include "ChipModel.hpp"
#include "ChipView.hpp"


std::shared_ptr<ChipController> ChipController::MakeChip(int player, float x, float y)
{
    auto controller = std::make_shared<ChipController>(player, x, y);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_ChipModel->m_ChipController = controller;
    controller->m_ChipView->m_ChipController = controller;

    return controller;
}


ChipController::ChipController(int player, float x, float y)
{
    m_ChipModel = std::make_shared<ChipModel>(player);
    AppDelegate::Get()->RegisterModel(m_ChipModel);

    const sf::Color playerColors[2] = {ColorPalette::Pred, ColorPalette::Cyan};
    const sf::Color highlightColors[2] = {ColorPalette::Cyan, ColorPalette::Pred};

    m_ChipView = std::make_shared<ChipView>(x, y, playerColors[player - 1], highlightColors[player - 1]);
    AppDelegate::Get()->RegisterView(m_ChipView);

    UpdateView();
}


void ChipController::Update()
{ }


void ChipController::HandleFocusReset()
{
    // TODO: remove
    SetHighlight(false);
}


void ChipController::HandleClick()
{
    // TODO: remove
    SetHighlight(true);
}


void ChipController::SetHighlight(bool highlight)
{
    m_ChipModel->SetHighlight(highlight);
    UpdateView();
}


int ChipController::GetPlayer() const
{
    return m_ChipModel->m_Player;
}


void ChipController::UpdateView()
{
    m_ChipView->EnableRing(m_ChipModel->m_Highlighted);
}
