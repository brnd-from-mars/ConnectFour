//
// Created by Brendan Berg on 08.03.22.
//

#pragma once

#include "EventObserver.hpp"


/*!
 * @brief Derived classes of the BaseView abstract class will represent the View-part of the MVC-element.
 */
class BaseView : public EventObserver
{

public:

    /*!
     * @brief Draw will be called by the AppDelegate once per frame. The derived class should draw its contents to the
     * screen in this function.
     */
    virtual void Draw() = 0;

    /*!
     * @brief Returns the layer of the view.
     *
     * @return layer of the view
     */
    int GetLayer() const
    {
        return m_Layer;
    }


protected:

    /*!
     * @brief Layer will be used by the AppDelegate to sort the views (0: background; higher number: foreground). It is
     * necessary that the layer shall be set by the derived class BEFORE the view gets registered to the AppDelegate.
     */
    int m_Layer = 0;


};
