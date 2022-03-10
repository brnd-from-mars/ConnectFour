//;
// Created by Brendan Berg on 10.03.22.
//

#include "GridFieldController.hpp"

#include "AppDelegate.hpp"

#include "GridFieldModel.hpp"
#include "GridFieldView.hpp"


std::shared_ptr<GridFieldController> GridFieldController::MakeGridFieldController(int column, int row)
{
    auto controller = std::make_shared<GridFieldController>(column, row);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_GridFieldModel->m_TextFieldController = controller;

    return controller;
}


GridFieldController::GridFieldController(int column, int row)
{
    m_GridFieldModel = std::make_shared<GridFieldModel>(column, row);
    AppDelegate::Get()->RegisterModel(m_GridFieldModel);

    m_GridFieldView = std::make_shared<GridFieldView>(100.0f + column * GridFieldView::m_Size,
                                                      1000.0f - row * GridFieldView::m_Size);
    AppDelegate::Get()->RegisterView(m_GridFieldView);
}


void GridFieldController::Update()
{

}
