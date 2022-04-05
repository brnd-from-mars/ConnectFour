//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>
#include <string>

#include "BaseModel.hpp"

class TextFieldController;


/*!
 * @brief ChipModel represents data associated with a text field
 */
class TextFieldModel : public BaseModel
{
    friend TextFieldController;


public:

    /*!
     * @brief No-op.
     */
    void Update() override;


private:

    /*!
     * @brief Adds a character to the stored string as long as it is a printable ascii-character
     *
     * @param character ascii character
     */
    void AddCharacter(char character);

    /*!
     * @brief Deletes the last character of the stored string as long as it is not empty already
     */
    void DeleteCharacter();

    /*!
     * @brief string that represents the entered text
     */
    std::string m_Text;


};
