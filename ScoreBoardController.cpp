//
// Created by Brendan Berg on 15.03.22.
//

#include "ScoreBoardModel.hpp"
#include "ScoreBoardView.hpp"
#include "ScoreBoardController.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<ScoreBoardController> ScoreBoardController::MakeScoreBoard(float x, float y, float width)
{
    auto controller = std::make_shared<ScoreBoardController>(x, y, width);
    AppDelegate::Get()->RegisterController(controller);

    return controller;
}


ScoreBoardController::ScoreBoardController(float x, float y, float width)
{
    m_ScoreBoardView = std::make_shared<ScoreBoardView>(x, y, width);
    AppDelegate::Get()->RegisterView(m_ScoreBoardView);

    m_ScoreBoardModel = std::make_shared<ScoreBoardModel>();
    AppDelegate::Get()->RegisterModel(m_ScoreBoardModel);
}


void ScoreBoardController::Update()
{ }
