//
// Created by Brendan Berg on 09.03.22.
//

#include "ChipModel.hpp"

#include "ChipController.hpp"


ChipModel::ChipModel(int player)
    : m_Player(player)
{

}


void ChipModel::Update()
{

}


void ChipModel::SetHighlight(bool highlight)
{
    m_Highlighted = highlight;
}
