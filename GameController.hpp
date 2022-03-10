//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

#include "SessionController.hpp"


class GameController : public BaseController
{

public:

    static std::shared_ptr<GameController> MakeGameController(int columns, int rows);

    GameController(int columns, int rows);

    virtual ~GameController();

    void Update() override;


private:

    std::weak_ptr<GameController> m_GameController;

    int m_Columns;

    int m_Rows;

    std::shared_ptr<SessionController> m_SessionController;


};
