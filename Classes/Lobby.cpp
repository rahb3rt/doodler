//
//  Lobby.cpp
//  Doodler
//
//  Created by Robert Davis on 7/19/16.
//
//

#include "Lobby.hpp"
#include "DrawingCanvas.hpp"

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
    
    soloButton->setPosition(Vec2(visibleSize.width / 0.75f, visibleSize.height * 0.35f));
    
    soloButton->loadTextures("soloButton.png", "soloButtonPressed.png");
    
    soloButton->addTouchEventListener(CC_CALLBACK_2(Lobby::soloPressed, this));
    
    this->addChild(soloButton);
    
    
    ui::Button* duoButton = ui::Button::create();
    
    duoButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    duoButton->setPosition(Vec2(visibleSize.width / 0.75f, visibleSize.height * 0.25f));
    
    duoButton->loadTextures("duoButton.png", "duoButtonPressed.png");
    
    duoButton->addTouchEventListener(CC_CALLBACK_2(Lobby::soloPressed, this));
    
    this->addChild(duoButton);
    
    

    
    
}

void Lobby::soloPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{

    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        Scene* scene = Scene::create();
        
        DrawingCanvas* drawingCanvas = DrawingCanvas::create();
        scene->addChild(drawingCanvas);
        
        Director::getInstance()->pushScene(scene);
    }
    
}