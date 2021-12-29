//
//  loadgame.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "loadgame.hpp"
Loadgame::Loadgame()
{
    string line;
    ifstream myfile ("savegame.txt");
    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            playerStats.push_back(line);
            cout << line << '\n';
        }
        myfile.close();
    }
    
    else cout << "Unable to open savegame";
}

vector<string> Loadgame::getPlayerStats()
{

        return playerStats;
  
}
