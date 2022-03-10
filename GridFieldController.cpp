//;
// Created by Brendan Berg on 10.03.22.
//

#include "GridFieldController.hpp"

#include <iostream>

#include "AppDelegate.hpp"

#include "GridFieldModel.hpp"
#include "GridFieldView.hpp"

#include "SessionController.hpp"


std::shared_ptr<GridFieldController> GridFieldController::MakeGridFieldController(const std::weak_ptr<SessionController>& sessionController, int column, int row)
{
    auto controller = std::make_shared<GridFieldController>(sessionController, column, row);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_GridFieldModel->m_GridFieldController = controller;
    controller->m_GridFieldView->m_GridFieldController = controller;

    return controller;
}


GridFieldController::GridFieldController(const std::weak_ptr<SessionController>& sessionController, int column, int row)
{
    m_GridFieldModel = std::make_shared<GridFieldModel>(column, row);
    AppDelegate::Get()->RegisterModel(m_GridFieldModel);

    m_GridFieldView = std::make_shared<GridFieldView>(100.0f + column * GridFieldView::m_Size,
                                                      1250.0f - row * GridFieldView::m_Size);
    AppDelegate::Get()->RegisterView(m_GridFieldView);
}


void GridFieldController::Update()
{

}


void GridFieldController::HandleClick()
{
    // TODO: feedback to session
    SetChip(1);
}


void GridFieldController::SetChip(int player)
{
    // chip already exists
    if (m_Chip)
    {
        return;
    }

    auto center = m_GridFieldView->GetCenter();
    m_Chip = std::make_shared<ChipController>(player, center.x, center.y);
}
