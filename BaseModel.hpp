//
// Created by Brendan Berg on 08.03.22.
//

#pragma once


/*!
 * @brief Derived classes of the BaseModel abstract class will represent the Model-part of the MVC-element.
 */
class BaseModel
{

public:

    /*!
     * @brief Update will be called by the AppDelegate once per frame.
     */
    virtual void Update() = 0;


};
