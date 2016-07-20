//
//  DrawingCanvas.cpp
//  Doodler
//
//  Created by Robert Davis on 7/19/16.
//
//

#include "DrawingCanvas.hpp"


using namespace cocos2d;

bool DrawingCanvas::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    background = LayerColor::create(Color4B(255, 255, 255, 255));
    
    this->addChild(background);
    
    drawNode = DrawNode::create();
    
    this->addChild(drawNode);
    
    return true;
}

void DrawingCanvas::onEnter()
{
    Node::onEnter();
    
    Size visibleSize = CCDirector::getInstance()->getVisibleSize();
    
    this->setContentSize(visibleSize);
    drawNode->setContentSize(visibleSize);
    
    setupTouchHandling();
}

void DrawingCanvas::setupTouchHandling()
{
    static Vec2 lastTouchPos;
  
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        lastTouchPos = drawNode->convertTouchToNodeSpace(touch);
        
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        
      Vec2 touchPos = drawNode->convertTouchToNodeSpace(touch);
        
        CCLOG("Touch Moved! x:%f y:%f", touchPos.x, touchPos.y);
        
        
        drawNode->drawSegment(lastTouchPos, touchPos, 4.0f, Color4F(0.0f, 0.0f, 0.0f, 1.0f));
        
        lastTouchPos = touchPos;
        
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    
    
}