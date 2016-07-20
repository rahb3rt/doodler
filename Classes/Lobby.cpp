//
//  Lobby.cpp
//  Doodler
//
//  Created by Robert Davis on 7/19/16.
//
//

#include "Lobby.hpp"


using namespace cocos2d;

bool Lobby::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(background);
    
    return true;
}

void Lobby::onEnter()
{
    Node::onEnter();
    setupUI();
}

void Lobby::setupUI()
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite* logo = Sprite::create("doodlerLogo.png");
    
    logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    logo->setPosition(Vec2(visibleSize.width * 1.35f, visibleSize.height * 0.75f));
    
    this->addChild(logo);
    
    
    //solo button
    
    
    
    
    ui::Button* soloButton = ui::Button::create();
    
    soloButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    soloButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height * 0.4f));
    
    soloButton->loadTextures("soloButton.png", "soloButtonPressed.png");
    
    soloButton->addTouchEventListener(CC_CALLBACK_2(Lobby::soloPressed, this));
    
    this->addChild(soloButton);
    
    
    

    
    
}

void Lobby::soloPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
}