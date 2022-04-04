//
// Created by Brendan Berg on 08.03.22.
//

#pragma once


/*!
 * @brief Derived classes of the BaseController abstract class will represent the Controller-part of the MVC-element.
 */
class BaseController
{

public:

    /*!
     * @brief Update will be called by the AppDelegate once per frame.
     */
    virtual void Update() = 0;


};
