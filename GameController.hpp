//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

#include "GameModel.hpp"

#include "SessionController.hpp"
#include "ScoreBoardController.hpp"
#include "TextView.hpp"


class GameController : public BaseController
{
    friend GameModel;


public:

    static std::shared_ptr<GameController> MakeGameController(int columns, int rows);

    GameController(int columns, int rows);

    virtual ~GameController();

    void Update() override;


private:

    void InitScoreBoard();

    std::shared_ptr<GameModel> m_GameModel;
    std::weak_ptr<GameController> m_GameController;

    std::shared_ptr<SessionController> m_Session;

    std::shared_ptr<ScoreBoardController> m_ScoreBoard;

    std::shared_ptr<TextView> m_HeadlineCyan;
    std::shared_ptr<TextView> m_HeadlineOrange;


};
