//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include "vendor/tinyxml2/tinyxml2.h"

#include "BaseModel.hpp"

#include "ConnectFourUtility.hpp"
#include "LinkedList.hpp"

class ScoreBoardController;


/*!
 * @brief ScoreBoardModel represents data associated with the ConnectFour ScoreBoard. The data is stored within a
 * LinkedList while the game is running. At the start of the game, an associated xml-file will be parsed to generate the
 * linked list. As the game is closed, the data and the changes will be stored back to the xml-file.
 */
class ScoreBoardModel : public BaseModel
{
    friend ScoreBoardController;


public:

    /*!
     * @brief Constructor loads the xml-file.
     */
    ScoreBoardModel();

    /*!
     * @brief Destructor saves the xml-file.
     */
    ~ScoreBoardModel();

    /*!
     * @brief No-op.
     */
    void Update() override;


private:

    /*!
     * @brief Adds the results of a game with a victory to the m_GameList and adjusts the entry in the m_PlayerList.
     *
     * @param game results of the played game
     */
    void AddGame(GameData game);

    /*!
     * @brief Adjusts the entry in the m_PlayerList after a tie has occurred.
     *
     * @param game results of the played game
     */
    void AddTie(const GameData& game);

    /*!
     * @brief Sorts the m_PlayerList according to the number of victories.
     */
    void SortPlayerListVictories();

    /*!
     * @brief Sorts the m_PlayerList according to the ratio between victories and total games.
     */
    void SortPlayerListKD();

    /*!
     * @brief Sorts the m_GameList according to the number of moves needed to gain the victory.
     */
    void SortGameListMoves();

    /*!
     * @brief Sorts the m_GameList according to the time needed to gain the victory.
     */
    void SortGameListTime();

    /*!
     * @brief Loads the associated xml-file if it exists and adds the games and players to the corresponding linked
     * lists.
     */
    void LoadXMLDocument();

    /*!
     * @brief Saves the data stored in the linked lists to the associated xml-file.
     */
    void SaveXMLDocument();

    /*!
     * @brief Static auxiliary function adds a game to the <Games> tag in a xml-file
     *
     * @param game results of the game to be added
     * @param nGames pointer to the <Games> tag
     * @param file pointer to the xml-file
     */
    static void AddGameToXMLDocument(GameData* game, tinyxml2::XMLElement* nGames, tinyxml2::XMLDocument* file);

    /*!
     * @brief Static auxiliary function adds a player to the <Players> tag in a xml-file
     *
     * @param player player data
     * @param nPlayers pointer to the <Players> tag
     * @param file pointer to the xml-file
     */
    static void AddPlayerToXMLDocument(PlayerData* player, tinyxml2::XMLElement* nPlayers, tinyxml2::XMLDocument* file);

    /*!
     * @brief LinkedList containing all game results
     */
    LinkedList<GameData> m_GameList;

    /*!
     * @brief LinkedList containing all players
     */
    LinkedList<PlayerData> m_PlayerList;


};
