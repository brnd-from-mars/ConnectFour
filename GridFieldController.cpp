//;
// Created by Brendan Berg on 10.03.22.
//

#include "GridFieldController.hpp"

#include "AppDelegate.hpp"

#include "GridFieldModel.hpp"
#include "GridFieldView.hpp"

#include "SessionController.hpp"


std::shared_ptr<GridFieldController> GridFieldController::MakeGridField(const std::weak_ptr<SessionController>& session,
                                                                        int column, int row)
{
    auto controller = std::make_shared<GridFieldController>(session, column, row);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_GridFieldModel->m_GridFieldController = controller;
    controller->m_GridFieldView->m_GridFieldController = controller;

    return controller;
}


GridFieldController::GridFieldController(const std::weak_ptr<SessionController>& session, int column, int row)
{
    m_GridFieldModel = std::make_shared<GridFieldModel>(column, row);
    AppDelegate::Get()->RegisterModel(m_GridFieldModel);

    m_GridFieldView = std::make_shared<GridFieldView>(50.0f + column * GridFieldView::m_Size,
                                                      625.0f - row * GridFieldView::m_Size);
    AppDelegate::Get()->RegisterView(m_GridFieldView);

    m_Session = session;
}


void GridFieldController::Update()
{ }


void GridFieldController::SetChip(int player)
{
    if (m_Chip)
    {
        return;
    }

    auto center = m_GridFieldView->GetCenter();
    m_Chip = ChipController::MakeChip(player, center.x, center.y);
}


void GridFieldController::SetHighlightChip(bool highlight)
{
    if (!m_Chip)
    {
        return;
    }

    m_Chip->SetHighlight(highlight);
}


bool GridFieldController::HasChip() const
{
    return m_Chip != nullptr;
}


int GridFieldController::GetPlayer() const
{
    if (!m_Chip)
    {
        return 0;
    }

    return m_Chip->GetPlayer();
}


int GridFieldController::GetColumn() const
{
    return m_GridFieldModel->m_Column;
}


int GridFieldController::GetRow() const
{
    return m_GridFieldModel->m_Row;
}


void GridFieldController::HandleClick()
{
    if (auto session = m_Session.lock())
    {
        session->HandleColumnClick(m_GridFieldModel->m_Column);
    }
}

