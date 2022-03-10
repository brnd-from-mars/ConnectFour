//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>
#include <vector>

#include "BaseController.hpp"

#include "ChipController.hpp"

class GameController;


class SessionController : public BaseController
{

public:

    static std::shared_ptr<SessionController> MakeSessionController(const std::weak_ptr<GameController>& gameController);

    explicit SessionController(std::weak_ptr<GameController> gameController);

    virtual ~SessionController();

    void Update() override;

    bool IsOngoing() const;


private:

    std::weak_ptr<GameController> m_GameController;

    std::vector<std::vector<std::shared_ptr<ChipController>>> m_ChipContainer;

    bool m_Ongoing = true; // TODO: outsource to model


};
