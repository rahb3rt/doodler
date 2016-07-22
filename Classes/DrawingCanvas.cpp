//
//  DrawingCanvas.cpp
//  Doodler
//
//  Created by Robert Davis on 7/19/16.
//
//

#include "DrawingCanvas.hpp"
#include "Constants.h"
#include "SceneManager.hpp"
#include "JSONPacker.hpp"


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
        
        if (this->networkedSession)
        {
            this->sendStrokeOverNetwork(lastTouchPos, touchPos, radius, selectedColor);
        }
        
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
        SceneManager::getInstance()->returnToLobby();
    }
}

void DrawingCanvas::colorChangePressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType){
    
    ui::Button* pressedButton = static_cast<ui::Button*>(pSender);
    

    
    
    if (eEventType == ui::Widget::TouchEventType::ENDED){
        
        selectedColor = Color4F(pressedButton->getColor());
        
        check->retain();
        check->removeFromParent();
        
        pressedButton->addChild(this->check);
        
        check->release();
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
    colorButtonLayout->setPosition(Vec2(visibleSize.width * 1.34f, 0.0f));
    this->addChild(colorButtonLayout);
    
    
    ui::Button* redButton = ui::Button::create();
    redButton->setAnchorPoint(Vec2(0.5f, 0.0f));
    redButton->setPosition(Vec2(visibleSize.width * 1 * (1.0f/6.0f), 0.0f));
    redButton->loadTextures("colorSwatch.png", "colorSwatch.png");
    redButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
    redButton->setColor(Color3B(COLOR_RED));
    colorButtonLayout->addChild(redButton);
    
    
    ui::Button* yellowButton = ui::Button::create();
    yellowButton->setAnchorPoint(Vec2(0.5f, 0.0f));
    yellowButton->setPosition(Vec2(visibleSize.width * 2 * (1.0f/6.0f), 0.0f));
    yellowButton->loadTextures("colorSwatch.png", "colorSwatch.png");
    yellowButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
    yellowButton->setColor(Color3B(COLOR_YELLOW));
    colorButtonLayout->addChild(yellowButton);
    
    ui::Button* greenButton = ui::Button::create();
    greenButton->setAnchorPoint(Vec2(0.5f, 0.0f));
    greenButton->setPosition(Vec2(visibleSize.width * 3 * (1.0f/6.0f), 0.0f));
    greenButton->loadTextures("colorSwatch.png", "colorSwatch.png");
    greenButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
    greenButton->setColor(Color3B(COLOR_GREEN));
    greenButton->addChild(this->check);
    colorButtonLayout->addChild(greenButton);
    
    
    ui::Button* blueButton = ui::Button::create();
    blueButton->setAnchorPoint(Vec2(0.5f, 0.0f));
    blueButton->setPosition(Vec2(visibleSize.width * 4 * (1.0f/6.0f), 0.0f));
    blueButton->loadTextures("colorSwatch.png", "colorSwatch.png");
    blueButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
    blueButton->setColor(Color3B(COLOR_BLUE));
    colorButtonLayout->addChild(blueButton);
    
    
    ui::Button* purpleButton = ui::Button::create();
    purpleButton->setAnchorPoint(Vec2(0.5f, 0.0f));
    purpleButton->setPosition(Vec2(visibleSize.width * 5 * (1.0f/6.0f), 0.0f));
    purpleButton->loadTextures("colorSwatch.png", "colorSwatch.png");
    purpleButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
    purpleButton->setColor(Color3B(COLOR_PURPLE));
    colorButtonLayout->addChild(purpleButton);
    
    

    
    
}

void DrawingCanvas::sendStrokeOverNetwork(Vec2 startPoint, Vec2 endPoint, float radius, Color4F color)
{
    JSONPacker::LineData lineData;
    lineData.startPoint = startPoint;
    lineData.endPoint = endPoint;
    lineData.radius = radius;
    lineData.color = color;
    
    std::string json = JSONPacker::packLineData(lineData);
    
    SceneManager::getInstance()->sendData(json.c_str(), json.length());
}


void DrawingCanvas::receivedData(const void* data, unsigned long length){
    
    const char* cstr = reinterpret_cast<const char*>(data);
    
    std::string json = std::string(cstr, length);
    
    JSONPacker::LineData lineData = JSONPacker::unpackLineDataJSON(json);
    
    drawNode->drawSegment(lineData.startPoint, lineData.endPoint, lineData.radius, lineData.color);
}



