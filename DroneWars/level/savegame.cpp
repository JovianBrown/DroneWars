//
//  savegame.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "savegame.hpp"
Savegame::Savegame(Player* player)
{
    std::ofstream playerSaveFile ("savegame.txt");
    if (playerSaveFile.is_open())
    {
        playerSaveFile << player->getHps()<<"\n";;
        playerSaveFile << player->getMaxHps()<<"\n";;
        playerSaveFile << player->getMaxAcc()<<"\n";;
        playerSaveFile << player->getMaxShield()<<"\n";;
        playerSaveFile << player->getRareElements()<<"\n";
        playerSaveFile << player->getPreciousMetals()<<"\n";;
        playerSaveFile << player->getEnergy()<<"\n";
        playerSaveFile << player->getLevel()<<"\n";
        playerSaveFile << player->getScore()<<"\n";
        playerSaveFile << player->getCredits()<<"\n";
        playerSaveFile << player->getCurrentWeapon()<<"\n";
        playerSaveFile.close();
    }
    else std::cout << "Unable to open file";
    
}
