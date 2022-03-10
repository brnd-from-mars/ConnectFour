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

    int GetColumns() const;

    int GetRows() const;


private:

    std::weak_ptr<GameController> m_GameController;

    std::shared_ptr<SessionController> m_SessionController;

    int m_Columns; // TODO: outsource to model

    int m_Rows;


};
