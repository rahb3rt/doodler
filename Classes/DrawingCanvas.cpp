//
//  DrawingCanvas.cpp
//  Doodler
//
//  Created by Robert Davis on 7/19/16.
//
//

#include "DrawingCanvas.hpp"
#include "Constants.h"


using namespace cocos2d;

bool DrawingCanvas::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    background = LayerColor::create(Color4B(COLOR_WHITE));
    
    this->addChild(background);
    
    drawNode = DrawNode::create();
    
    this->addChild(drawNode);
    
    selectedColor = COLOR_GREEN;
    
    
    
    return true;
}


void DrawingCanvas::onEnter()
{
    Node::onEnter();
    
    Size visibleSize = CCDirector::getInstance()->getVisibleSize();
    
    this->setContentSize(visibleSize);
    drawNode->setContentSize(visibleSize);
    
    setupTouchHandling();
    setupMenus();
}



void DrawingCanvas::setupTouchHandling()
{
    static Vec2 lastTouchPos;
    static float lastRadius = INITIAL_RADIUS;
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        lastTouchPos = drawNode->convertTouchToNodeSpace(touch);
        lastRadius = INITIAL_RADIUS;
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = drawNode->convertTouchToNodeSpace(touch);
        
        float distance = lastTouchPos.distance(touchPos);
        
        float dt = 1.0f / 60.0f;
        float rc = 1.0f;
        float alpha = dt / (rc + dt);
        float radius = (alpha * distance) + (1.0f - alpha) * lastRadius;
        
        drawNode->drawSegment(lastTouchPos, touchPos, radius, selectedColor);
        
        lastRadius = radius;
        lastTouchPos = touchPos;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    
    
}

void DrawingCanvas::clearPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        drawNode->clear();
    }
}

void DrawingCanvas::backPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->popScene();
    }
}


void DrawingCanvas::setupMenus(){
    
    Size visibleSize = CCDirector::getInstance()->getVisibleSize();
    
    this->setContentSize(visibleSize);
    drawNode->setContentSize(visibleSize);
    
    ui::Button* clearButton = ui::Button::create();
    clearButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    clearButton->setPosition(Vec2(visibleSize.width, visibleSize.height));
    clearButton->loadTextures("clearButton.png", "clearButtonPressed.png");
    clearButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::clearPressed, this));
    this->addChild(clearButton);
    
    ui::Button* backButton = ui::Button::create();
    backButton->setAnchorPoint(Vec2(1.0f, 1.0f));
    backButton->setPosition(Vec2(visibleSize.width  , visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::backPressed, this));
    this->addChild(backButton);
    
    
    check = Sprite::create("checkMark.png");
    check->setAnchorPoint(Vec2(0.5f, 0.5f));
    check->setNormalizedPosition(Vec2(0.5f, 0.5f));
    
    
    Node* colorButtonLayout = Node::create();
    colorButtonLayout->setContentSize(Size(visibleSize.width, visibleSize.height * 0.2f));
    colorButtonLayout->setAnchorPoint(Vec2(0.5f, 0.0f));
    colorButtonLayout->setPosition(Vec2(visibleSize.width / 2.0f, 0.0f));
    this->addChild(colorButtonLayout);
    
    
    for (int i = 1; i <= 5; ++i)
    {
        ui::Button* colorButton = ui::Button::create();
        colorButton->setAnchorPoint(Vec2(0.5f, 0.0f));
        colorButton->setPosition(Vec2(visibleSize.width * i * (1.0f/6.0f), 0.0f));
        colorButton->loadTextures("colorSwatch.png", "colorSwatch.png");
        colorButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
        colorButton->setColor(Color3B(COLOR_BLUE));
        colorButtonLayout->addChild(colorButton);
    }
    
    
    
    
}




