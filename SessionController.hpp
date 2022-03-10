//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>
#include <vector>

#include "BaseController.hpp"

#include "GridFieldController.hpp"

class GameController;


class SessionController : public BaseController
{

public:

    // TODO: remove parent controller from factory and constructor
    static std::shared_ptr<SessionController> MakeSessionController(const std::weak_ptr<GameController>& gameController);

    explicit SessionController(std::weak_ptr<GameController> gameController);

    virtual ~SessionController();

    void Update() override;

    void InitGrid();

    bool IsOngoing() const;


private:

    std::weak_ptr<SessionController> m_SessionController;

    std::weak_ptr<GameController> m_GameController;

    std::vector<std::vector<std::shared_ptr<GridFieldController>>> m_Grid;

    bool m_Ongoing = true; // TODO: outsource to model


};
