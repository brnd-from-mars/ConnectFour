//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

class GameController;


class SessionController : public BaseController
{

public:

    static std::shared_ptr<SessionController> MakeSessionController(std::weak_ptr<GameController> gameController);

    explicit SessionController(std::weak_ptr<GameController> gameController);

    virtual ~SessionController();

    void Update() override;

    bool IsOngoing() const;


private:

    std::weak_ptr<GameController> m_GameController;

    bool m_Ongoing = true;

    int i = 90;

};
