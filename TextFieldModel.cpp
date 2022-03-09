//
// Created by Brendan Berg on 09.03.22.
//

#include "TextFieldModel.hpp"

// TODO: remove iostream
#include <iostream>


void TextFieldModel::Update()
{
    std::cout << m_Text << std::endl;
}


void TextFieldModel::AddCharacter(char character)
{
    m_Text.push_back(character);
}


void TextFieldModel::DeleteCharacter()
{
    if (m_Text.empty())
    {
        return;
    }

    m_Text.pop_back();
}
