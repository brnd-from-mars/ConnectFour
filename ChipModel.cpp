//
// Created by Brendan Berg on 09.03.22.
//

#include "ChipModel.hpp"


ChipModel::ChipModel(int player, int column, int row)
    : m_Player(player), m_Column(column), m_Row(row)
{

}


void ChipModel::Update()
{

}


void ChipModel::SetHighlight(bool highlight)
{
    m_Highlighted = highlight;
}
