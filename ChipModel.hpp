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

    ChipModel(int player, int column, int row);

    void Update() override;

    void SetHighlight(bool highlight);


private:

    std::weak_ptr<ChipController> m_ChipController;

    int m_Player;

    int m_Column;

    int m_Row;

    bool m_Highlighted = false;


};
