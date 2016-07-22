//
//  SceneManager.hpp
//  Doodler
//
//  Created by Robert Davis on 7/21/16.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include "NetworkingWrapper.h"



class DrawingCanvas;

class SceneManager : public NetworkingDelegate{
    
public:
    static SceneManager* getInstance();
    void enterSoloGame();
    void returnToLobby();
    void connectAndEnterNetworkedGame();
    void sendData(const void *data, unsigned long length);

private:
    void receivedData(const void* data, unsigned long length) override;
    void stateChanged(ConnectionState state) override;
    SceneManager();
    ~SceneManager();
    DrawingCanvas* drawingCanvas;
    NetworkingWrapper* networkingWrapper;
    void loadDrawingScene(bool networked);
    
    
};

#endif /* SceneManager_hpp */
