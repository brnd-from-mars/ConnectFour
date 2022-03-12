//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>
#include <vector>

#include "BaseController.hpp"

#include "GridFieldController.hpp"
#include "TextFieldController.hpp"

class SessionModel;

class GameController;


class SessionController : public BaseController
{
    friend SessionModel;


public:

    static std::shared_ptr<SessionController> MakeSessionController(const std::weak_ptr<GameController>& gameController,
                                                                    int columns, int rows);

    explicit SessionController(std::weak_ptr<GameController> gameController, int columns, int rows);

    virtual ~SessionController();

    void Update() override;

    void InitNamePlayer1();

    void InitNamePlayer2();

    void InitGrid();

    void HandleColumnClick(int column);

    void HandleNamePlayer1Enter();

    void HandleNamePlayer2Enter();

    bool IsOngoing() const;

    int GetPlayerAt(int column, int row) const;


private:

    std::shared_ptr<SessionModel> m_SessionModel;
    std::weak_ptr<SessionController> m_SessionController;

    std::weak_ptr<GameController> m_GameController;

    std::vector<std::vector<std::shared_ptr<GridFieldController>>> m_Grid;

    std::shared_ptr<TextFieldController> m_NamePlayer1;
    std::shared_ptr<TextFieldController> m_NamePlayer2;


};
