//
// Created by Brendan Berg on 09.03.22.
//

#include "TextFieldModel.hpp"


void TextFieldModel::Update()
{ }


void TextFieldModel::AddCharacter(char character)
{
    // is the character printable?
    if (0x20 < character && character < 0x7f)
    {
        m_Text.push_back(character);
    }
}


void TextFieldModel::DeleteCharacter()
{
    if (m_Text.empty())
    {
        return;
    }

    m_Text.pop_back();
}
