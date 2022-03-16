//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

#include "ConnectFourUtility.hpp"

#include "ButtonController.hpp"

class ScoreBoardModel;
class ScoreBoardView;


class ScoreBoardController : public BaseController
{
    friend ScoreBoardView;


public:

    static std::shared_ptr<ScoreBoardController>MakeScoreBoard(float x, float y, float width);

    ScoreBoardController(float x, float y, float width);

    void Update() override;

    void AddGame(GameData game);

    void AddTie(const GameData& game);


private:

    void InitButtons();

    void PrevScoreBoard();
    void NextScoreBoard();

    void UpdateView();

    std::shared_ptr<ScoreBoardModel> m_ScoreBoardModel;
    std::shared_ptr<ScoreBoardView> m_ScoreBoardView;
    std::weak_ptr<ScoreBoardController> m_ScoreBoardController;

    std::shared_ptr<ButtonController> m_PrevScoreBoardButton;
    std::shared_ptr<ButtonController> m_NextScoreBoardButton;

    enum class ScoreBoardType
    {
        mostVictories,
        bestKD,
        leastMoves,
        leastTime,
        num
    } m_CurrentScoreBoard = ScoreBoardType::bestKD;


};
