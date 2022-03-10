//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"


class GameController : public BaseController
{

public:

    static std::shared_ptr<GameController> MakeGameController(int columns, int rows);

    GameController(int columns, int rows);

    void Update() override;


private:

    int m_Columns;

    int m_Rows;


};
