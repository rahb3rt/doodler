//
//  JSONPacker.hpp
//  Doodler
//
//  Created by Robert Davis on 7/22/16.
//
//

#ifndef JSONPacker_hpp
#define JSONPacker_hpp

#include <stdio.h>
#include "cocos2d.h"

namespace JSONPacker
{
    
    struct LineData
    {
        cocos2d::Vec2 startPoint;
        cocos2d::Vec2 endPoint;
        cocos2d::Color4F color;
        float radius;
    };
    
    LineData unpackLineDataJSON(std::string json);
    std::string packLineData(LineData lineData);
    
}

#endif /* JSONPacker_hpp */
