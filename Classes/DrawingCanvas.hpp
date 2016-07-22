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
#include "ui/CocosGUI.h"

class DrawingCanvas : public cocos2d::Node
{
public:
    CREATE_FUNC(DrawingCanvas);
    bool getNetworkedSession(){
        
        return networkedSession;
    }
    
    void setNetworkedSession(bool value){
        
        networkedSession = value;
    }
    
    void receivedData(const void* data, unsigned long length);
    
    
    

    
    
    
protected:
    cocos2d::DrawNode* drawNode;
    cocos2d::LayerColor* background;
    cocos2d::Sprite* check;
    cocos2d::Color4F selectedColor;

    

    bool init() override;
    void onEnter() override;
    bool networkedSession;
    void setupTouchHandling();
    void setupMenus();
    void backPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void clearPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void colorChangePressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void sendStrokeOverNetwork(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint, float radius, cocos2d::Color4F color);
    
    
    
    
};

#endif /* DrawingCanvas_hpp */
