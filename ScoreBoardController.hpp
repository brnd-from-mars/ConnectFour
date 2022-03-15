//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

class ScoreBoardView;


class ScoreBoardController : public BaseController
{
    friend ScoreBoardView;


public:

    static std::shared_ptr<ScoreBoardController>MakeScoreBoard(float x, float y, float width);

    ScoreBoardController(float x, float y, float width);

    void Update() override;


private:

    std::shared_ptr<ScoreBoardView> m_ScoreBoardView;


};
