//
//  DrawingCanvas.hpp
//  Doodler
//
//  Created by Robert Davis on 7/19/16.
//
//

#ifndef DrawingCanvas_hpp
#define DrawingCanvas_hpp

#include "cocos2d.h"

class DrawingCanvas : public cocos2d::Node
{
public:
    CREATE_FUNC(DrawingCanvas);
    
protected:
    cocos2d::DrawNode* drawNode;
    cocos2d::LayerColor* background;
    
    bool init() override;
    void onEnter() override;
    void setupTouchHandling();
};

#endif /* DrawingCanvas_hpp */
