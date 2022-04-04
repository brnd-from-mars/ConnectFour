//
// Created by Brendan Berg on 08.03.22.
//

#pragma once

#include <SFML/Graphics.hpp>


/*!
 * @brief Derived classes of the EventObserver abstract class will be able to handle events pushed by the AppDelegate.
 */
class EventObserver
{

public:

    /*!
     * @brief HandleFocusReset in all EventObservers will get called by the AppDelegate before it pushes a following
     * mousePressed event.
     *
     * @return Did the class handle the focus reset?
     */
    virtual bool HandleFocusReset() = 0;

    /*!
     * @brief Handle in all EventObservers will get called by the AppDelegate until one EventObserver successfully
     * handles the result and returns true.
     *
     * @param event Occurred SFML-Event
     * @return Did the class handle the event?
     */
    virtual bool Handle(sf::Event event) = 0;


};
