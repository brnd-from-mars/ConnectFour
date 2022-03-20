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


void ScoreBoardModel::AddGame(GameData data)
{
    auto winningPlayerName = data.winningPlayer;
    auto loosingPlayerName = data.loosingPlayer;

    m_GameList.AddElement(std::move(data));

    auto winningPlayer = m_PlayerList.Find([&winningPlayerName](PlayerData* player) -> bool
                                           {
                                               return player->name == winningPlayerName;
                                           });
    if (winningPlayer)
    {
        ++winningPlayer->games;
        ++winningPlayer->victories;
    }
    else
    {
        PlayerData player = {winningPlayerName, 1, 1};
        m_PlayerList.AddElement(player);
    }

    auto loosingPlayer = m_PlayerList.Find([&loosingPlayerName](PlayerData* player) -> bool
                                           {
                                               return player->name == loosingPlayerName;
                                           });
    if (loosingPlayer)
    {
        ++loosingPlayer->games;
    }
    else
    {
        PlayerData player = {loosingPlayerName, 1, 0};
        m_PlayerList.AddElement(player);
    }
}


void ScoreBoardModel::AddTie(const GameData& data)
{
    auto playerName1 = data.winningPlayer;
    auto playerName2 = data.loosingPlayer;

    auto player1 = m_PlayerList.Find([&playerName1](PlayerData* player)
                                     {
                                         return player->name == playerName1;
                                     });
    if (player1)
    {
        ++player1->games;
    }
    else
    {
        PlayerData player = {playerName1, 1, 0};
        m_PlayerList.AddElement(player);
    }

    auto player2 = m_PlayerList.Find([&playerName2](PlayerData* player)
                                     {
                                         return player->name == playerName2;
                                     });
    if (player2)
    {
        ++player2->games;
    }
    else
    {
        PlayerData player = {playerName2, 1, 0};
        m_PlayerList.AddElement(player);
    }
}


void ScoreBoardModel::LoadXMLDocument()
{
    tinyxml2::XMLDocument file;
    if (file.LoadFile("ScoreBoard.xml") != tinyxml2::XML_SUCCESS)
    {
        std::clog << "ScoreBoard.xml not found" << std::endl;
        return;
    }

    tinyxml2::XMLNode* nScoreBoard = file.FirstChild();

    tinyxml2::XMLNode* nGames = nScoreBoard->FirstChildElement("Games");
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

    tinyxml2::XMLNode* nPlayers = nScoreBoard->FirstChildElement("Players");
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


void ScoreBoardModel::SaveXMLDocument()
{
    tinyxml2::XMLDocument file;

    tinyxml2::XMLElement* nScoreBoard = file.NewElement("ScoreBoard");
    file.InsertFirstChild(nScoreBoard);

    tinyxml2::XMLElement* nGames = file.NewElement("Games");
    nScoreBoard->InsertEndChild(nGames);
    m_GameList.ForEach([nGames, &file](GameData* game)
                       {
                           AddGameToXMLDocument(game, nGames, &file);
                       });

    tinyxml2::XMLElement* nPlayers = file.NewElement("Players");
    nScoreBoard->InsertEndChild(nPlayers);
    m_PlayerList.ForEach([nPlayers, &file](PlayerData* player)
                         {
                             AddPlayerToXMLDocument(player, nPlayers, &file);
                         });

    file.SaveFile("ScoreBoard.xml");
}


void ScoreBoardModel::AddGameToXMLDocument(GameData* game, tinyxml2::XMLElement* nGames, tinyxml2::XMLDocument* file)
{
    tinyxml2::XMLElement* nGame = file->NewElement("Game");
    nGames->InsertEndChild(nGame);

    tinyxml2::XMLElement* nElement = nullptr;

    nElement = file->NewElement("WinningPlayer");
    nElement->SetText(game->winningPlayer.c_str());
    nGame->InsertEndChild(nElement);

    nElement = file->NewElement("LoosingPlayer");
    nElement->SetText(game->loosingPlayer.c_str());
    nGame->InsertEndChild(nElement);

    nElement = file->NewElement("Moves");
    nElement->SetText(game->moves);
    nGame->InsertEndChild(nElement);

    nElement = file->NewElement("Time");
    nElement->SetText(game->time);
    nGame->InsertEndChild(nElement);
}


void ScoreBoardModel::AddPlayerToXMLDocument(PlayerData* player,
                                             tinyxml2::XMLElement* nPlayers, tinyxml2::XMLDocument* file)
{
    tinyxml2::XMLNode* nPlayer = file->NewElement("Player");
    nPlayers->InsertEndChild(nPlayer);

    tinyxml2::XMLElement* nElement = nullptr;

    nElement = file->NewElement("Name");
    nElement->SetText(player->name.c_str());
    nPlayer->InsertEndChild(nElement);

    nElement = file->NewElement("Games");
    nElement->SetText(player->games);
    nPlayer->InsertEndChild(nElement);

    nElement = file->NewElement("Victories");
    nElement->SetText(player->victories);
    nPlayer->InsertEndChild(nElement);
}
