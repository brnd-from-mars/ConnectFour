//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>
#include <string>

#include "BaseModel.hpp"

class TextFieldController;


class TextFieldModel : public BaseModel
{
    friend TextFieldController;


public:

    void Update() override;

    void AddCharacter(char character);

    void DeleteCharacter();


private:

    std::string m_Text;


};
