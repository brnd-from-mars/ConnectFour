//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include "BaseModel.hpp"

#include "ConnectFourUtility.hpp"
#include "LinkedList.hpp"

class ScoreBoardController;


class ScoreBoardModel : public BaseModel
{
    friend ScoreBoardController;


public:

    ScoreBoardModel();

    void Update() override;


private:

    LinkedList<GameData> m_GameList;


};
