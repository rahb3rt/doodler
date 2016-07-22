//
//  SceneManager.cpp
//  Doodler
//
//  Created by Robert Davis on 7/21/16.
//
//

#include "SceneManager.hpp"
#include "DrawingCanvas.hpp"
#include "JSONPacker.hpp"


using namespace cocos2d;



static SceneManager* sharedSceneManager = nullptr;

DrawingCanvas* drawingCanvas = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (! sharedSceneManager)
    {
        sharedSceneManager = new SceneManager();
    }
    
    return sharedSceneManager;
}

void SceneManager::receivedData(const void *data, unsigned long length)
{
    if (drawingCanvas)
    {
        drawingCanvas->receivedData(data, length);
    }
}



void SceneManager::stateChanged(ConnectionState state){

    switch (state)
    {
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
            
        case ConnectionState::CONNECTING:
            CCLOG("Connecting...");
            break;
            
        case ConnectionState::CONNECTED:
            CCLOG("Connected!");
            break;
    }
    
    if (!drawingCanvas)
    {
        this->loadDrawingScene(true);
    }
};

void SceneManager::connectAndEnterNetworkedGame(){
    
    networkingWrapper->attemptToJoinGame();
    

}


SceneManager::SceneManager()
{
    networkingWrapper = new NetworkingWrapper();
    networkingWrapper->setDelegate(this);
    
}

SceneManager::~SceneManager()
{
    delete networkingWrapper;
    
}

void SceneManager::enterSoloGame(){

    this->loadDrawingScene(false);
}

void SceneManager::loadDrawingScene(bool networked)
{
    auto scene = Scene::create();
    
    drawingCanvas = DrawingCanvas::create();
    drawingCanvas->setNetworkedSession(networked);
    
    scene->addChild(drawingCanvas);
    
    Director::getInstance()->pushScene(scene);
}

void SceneManager::returnToLobby()
{
    if (drawingCanvas)
    {
        Director::getInstance()->popScene();
        drawingCanvas = nullptr;
    }
}

void SceneManager::sendData(const void *data, double length){
    
    if(drawingCanvas){
        networkingWrapper->sendData(data, length);
        
    }
}
