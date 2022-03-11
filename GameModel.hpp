//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseModel.hpp"

class GameController;


class GameModel : public BaseModel
{
    friend GameController;


public:

    GameModel(int columns, int rows);

    void Update() override;


private:

    std::weak_ptr<GameController> m_GameController;

    int m_Columns;
    int m_Rows;


};
