//
//  Lobby.hpp
//  Doodler
//
//  Created by Robert Davis on 7/19/16.
//
//

#ifndef __Doodler__Lobby__
#define __Doodler__Lobby__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class Lobby : public cocos2d::Node
{
public:
    CREATE_FUNC(Lobby);
    
protected:
    bool init() override;
    void onEnter() override;
    void setupUI();
    void soloPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

};

#endif /* defined(__Doodler__Lobby__) */