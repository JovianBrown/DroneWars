//
//  background.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef background_hpp
#define background_hpp

#include "object.hpp"
class Background : public Object
{
public:
    Background()
    :bgHeight(640),bgWidth(640),offset(-640),speed(4)
    {
        
    }
    void update(int &levelHeight);
    void setSpeed(int s)
    {
        speed = s;
    }
private:
    const int bgHeight;
    const int bgWidth;
    const int offset;
    int speed;
    int theseTicks;
    int startTick;
};
#endif /* background_hpp */
