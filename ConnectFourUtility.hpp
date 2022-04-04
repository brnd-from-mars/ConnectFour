//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include <string>

#include <SFML/Graphics.hpp>


/*!
 * @brief GameData struct stores the result of a ConnectFour Game. The fields winningPlayer and loosingPlayer are
 * interchangeable in case of a tie.
 */
struct GameData
{
    /*!
     * @brief name of the winning player
     */
    std::string winningPlayer;

    /*!
     * @brief name of the loosing player
     */
    std::string loosingPlayer;

    /*!
     * @brief number of moves until the end of the game by the finishing player
     */
    int moves;

    /*!
     * @brief seconds until the end of the game
     */
    int time;
};


/*!
 * @brief PlayerData stores the summary over all games played by a player.
 */
struct PlayerData
{
    /*!
     * @brief name of the player
     */
    std::string name;

    /*!
     * @brief number of games the player played
     */
    int games;

    /*!
     * @brief number of games the player won
     */
    int victories;
};


/*!
 * @brief Names for all used colors in the game.
 */
namespace ColorPalette
{
    /// @brief a gorgeous gray
    const sf::Color Basestar = sf::Color(12, 20, 31);
    /// @brief a even darker gorgeous gray
    const sf::Color BasestarDark = sf::Color(8, 13, 21);
    /// @brief a light gorgeous gray (also, its blue value is 42!!!)
    const sf::Color BasestarLight = sf::Color(16, 27, 42);

    /// @brief a lil highlight color, as a treat
    const sf::Color Orange = sf::Color(233, 126, 22);
    /// @brief pink + red = ???
    const sf::Color Pred = sf::Color(255, 0, 85);
    /// @brief pretty basic or not?
    const sf::Color Cyan = sf::Color(0, 255, 255);
}
