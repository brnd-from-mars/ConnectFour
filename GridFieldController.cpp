//
// Created by Brendan Berg on 10.03.22.
//

#include "GridFieldController.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<GridFieldController> GridFieldController::MakeGridFieldController(int column, int row)
{
    auto controller = std::make_shared<GridFieldController>(column, row);
    AppDelegate::Get()->RegisterController(controller);

    return std::shared_ptr<GridFieldController>();
}


GridFieldController::GridFieldController(int column, int row)
{

}


void GridFieldController::Update()
{

}
