//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include "BaseModel.hpp"

class ChipController;


class ChipModel : public BaseModel
{
    friend ChipController;


public:

    explicit ChipModel(int player);

    void Update() override;


private:

    void SetHighlight(bool highlight);

    std::weak_ptr<ChipController> m_ChipController;

    int m_Player;

    bool m_Highlighted = false;


};
