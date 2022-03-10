//
// Created by Brendan Berg on 10.03.22.
//

#include "GameController.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<GameController> GameController::MakeGameController(int columns, int rows)
{
    auto controller = std::make_shared<GameController>(columns, rows);
    AppDelegate::Get()->RegisterController(controller);

    return std::shared_ptr<GameController>();
}


GameController::GameController(int columns, int rows)
    : m_Columns(columns), m_Rows(rows)
{

}


void GameController::Update()
{

}
