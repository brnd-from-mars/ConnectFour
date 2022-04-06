//
// Created by Brendan Berg on 15.03.22.
//

#include "ScoreBoardModel.hpp"

#include "ConnectFourUtility.hpp"

#include <iostream>


ScoreBoardModel::ScoreBoardModel()
{
    LoadXMLDocument();
}


ScoreBoardModel::~ScoreBoardModel()
{
    SaveXMLDocument();
}


void ScoreBoardModel::Update()
{ }


void ScoreBoardModel::AddGame(GameData game)
{
    auto winningPlayerName = game.winningPlayer;
    auto loosingPlayerName = game.loosingPlayer;

    // add game to database
    m_GameList.AddElement(std::move(game));

    // find winning player in database
    auto winningPlayer = m_PlayerList.Find([&winningPlayerName](PlayerData* player) -> bool
                                           {
                                               return player->name == winningPlayerName;
                                           });
    if (winningPlayer)
    {
        // increment games and victories count if winning player already in database
        ++winningPlayer->games;
        ++winningPlayer->victories;
    }
    else
    {
        // create new player and set games and victories to 1 if not already in database
        PlayerData player = {winningPlayerName, 1, 1};
        m_PlayerList.AddElement(player);
    }

    // find loosing player in database
    auto loosingPlayer = m_PlayerList.Find([&loosingPlayerName](PlayerData* player) -> bool
                                           {
                                               return player->name == loosingPlayerName;
                                           });
    if (loosingPlayer)
    {
        // increment games count if winning player already in database
        ++loosingPlayer->games;
    }
    else
    {
        // create new player and set games to 1 and victories to 0 if not already in database
        PlayerData player = {loosingPlayerName, 1, 0};
        m_PlayerList.AddElement(player);
    }
}


void ScoreBoardModel::AddTie(const GameData& game)
{
    auto playerName1 = game.winningPlayer;
    auto playerName2 = game.loosingPlayer;

    // find player1 in database
    auto player1 = m_PlayerList.Find([&playerName1](PlayerData* player)
                                     {
                                         return player->name == playerName1;
                                     });
    if (player1)
    {
        // increment games count if player1 already in database
        ++player1->games;
    }
    else
    {
        // create new player and set games to 1 and victories to 0 if not already in database
        PlayerData player = {playerName1, 1, 0};
        m_PlayerList.AddElement(player);
    }

    // find player2 in database
    auto player2 = m_PlayerList.Find([&playerName2](PlayerData* player)
                                     {
                                         return player->name == playerName2;
                                     });
    if (player2)
    {
        // increment games count if player2 already in database
        ++player2->games;
    }
    else
    {
        // create new player and set games to 1 and victories to 0 if not already in database
        PlayerData player = {playerName2, 1, 0};
        m_PlayerList.AddElement(player);
    }
}



void ScoreBoardModel::SortPlayerListVictories()
{
    m_PlayerList.Sort([](PlayerData* player) -> int
                      {
                          return player->victories;
                      });
}


void ScoreBoardModel::SortPlayerListKD()
{
    m_PlayerList.Sort([](PlayerData* player) -> int
                      {
                          return 100 * player->victories / player->games;
                      });
}


void ScoreBoardModel::SortGameListMoves()
{
    m_GameList.Sort([](GameData* game) -> int
                    {
                        return game->moves;
                    });
}


void ScoreBoardModel::SortGameListTime()
{
    m_GameList.Sort([](GameData* game) -> int
                    {
                        return game->time;
                    });
}


void ScoreBoardModel::LoadXMLDocument()
{
    // load xml-file and abort if is not found
    tinyxml2::XMLDocument file;
    if (file.LoadFile("ScoreBoard.xml") != tinyxml2::XML_SUCCESS)
    {
        std::clog << "ScoreBoard.xml not found" << std::endl;
        return;
    }

    // go the the <ScoreBoard> tag
    tinyxml2::XMLNode* nScoreBoard = file.FirstChild();

    // go the the <Games> tag
    tinyxml2::XMLNode* nGames = nScoreBoard->FirstChildElement("Games");
    // iterate through the <Game> tags and add them to the m_GameList LinkedList
    tinyxml2::XMLNode* nGame = nGames->FirstChild();
    while (nGame != nullptr)
    {
        GameData game = {nGame->FirstChildElement("WinningPlayer")->GetText(),
                         nGame->FirstChildElement("LoosingPlayer")->GetText(),
                         static_cast<int>(strtol(nGame->FirstChildElement("Moves")->GetText(), nullptr, 10)),
                         static_cast<int>(strtol(nGame->FirstChildElement("Time")->GetText(), nullptr, 10))};
        m_GameList.AddElement(game);
        nGame = nGame->NextSibling();
    }

    // go the the <Players> tag
    tinyxml2::XMLNode* nPlayers = nScoreBoard->FirstChildElement("Players");
    // iterate through the <Player> tags and add them to the m_PlayerList LinkedList
    tinyxml2::XMLNode* nPlayer = nPlayers->FirstChild();
    while (nPlayer != nullptr)
    {
        PlayerData player = {nPlayer->FirstChildElement("Name")->GetText(),
                             static_cast<int>(strtol(nPlayer->FirstChildElement("Games")->GetText(), nullptr, 10)),
                             static_cast<int>(strtol(nPlayer->FirstChildElement("Victories")->GetText(), nullptr, 10))};
        m_PlayerList.AddElement(player);
        nPlayer = nPlayer->NextSibling();
    }
}


void ScoreBoardModel::SaveXMLDocument()
{
    // Create empty file
    tinyxml2::XMLDocument file;

    // create <ScoreBoard> tag
    tinyxml2::XMLElement* nScoreBoard = file.NewElement("ScoreBoard");
    file.InsertFirstChild(nScoreBoard);

    // create <Games> tag within <ScoreBoard>
    tinyxml2::XMLElement* nGames = file.NewElement("Games");
    nScoreBoard->InsertEndChild(nGames);
    // iterate through games in m_GameList LinkedList and add them as <Game> to <Games>
    m_GameList.ForEach([nGames, &file](GameData* game)
                       {
                           AddGameToXMLDocument(game, nGames, &file);
                       });

    // create <Players> tag within <ScoreBoard>
    tinyxml2::XMLElement* nPlayers = file.NewElement("Players");
    nScoreBoard->InsertEndChild(nPlayers);
    // iterate through players in m_PlayerList LinkedList and add them as <Player> to <Players>
    m_PlayerList.ForEach([nPlayers, &file](PlayerData* player)
                         {
                             AddPlayerToXMLDocument(player, nPlayers, &file);
                         });

    file.SaveFile("ScoreBoard.xml");
}


void ScoreBoardModel::AddGameToXMLDocument(GameData* game, tinyxml2::XMLElement* nGames, tinyxml2::XMLDocument* file)
{
    // create <Game> tag within <Games>
    tinyxml2::XMLElement* nGame = file->NewElement("Game");
    nGames->InsertEndChild(nGame);

    tinyxml2::XMLElement* nElement = nullptr;

    // create <WinningPlayer> tag within <Game>
    nElement = file->NewElement("WinningPlayer");
    nElement->SetText(game->winningPlayer.c_str());
    nGame->InsertEndChild(nElement);

    // create <LoosingPlayer> tag within <Game>
    nElement = file->NewElement("LoosingPlayer");
    nElement->SetText(game->loosingPlayer.c_str());
    nGame->InsertEndChild(nElement);

    // create <Moves> tag within <Game>
    nElement = file->NewElement("Moves");
    nElement->SetText(game->moves);
    nGame->InsertEndChild(nElement);

    // create <Time> tag within <Game>
    nElement = file->NewElement("Time");
    nElement->SetText(game->time);
    nGame->InsertEndChild(nElement);
}


void ScoreBoardModel::AddPlayerToXMLDocument(PlayerData* player,
                                             tinyxml2::XMLElement* nPlayers, tinyxml2::XMLDocument* file)
{
    // create <Player> tag within <Players>
    tinyxml2::XMLNode* nPlayer = file->NewElement("Player");
    nPlayers->InsertEndChild(nPlayer);

    tinyxml2::XMLElement* nElement = nullptr;

    // create <Name> tag within <Player>
    nElement = file->NewElement("Name");
    nElement->SetText(player->name.c_str());
    nPlayer->InsertEndChild(nElement);

    // create <Games> tag within <Player>
    nElement = file->NewElement("Games");
    nElement->SetText(player->games);
    nPlayer->InsertEndChild(nElement);

    // create <Victories> tag within <Player>
    nElement = file->NewElement("Victories");
    nElement->SetText(player->victories);
    nPlayer->InsertEndChild(nElement);
}
