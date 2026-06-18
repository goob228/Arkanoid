#ifndef GAME_H
#define GAME_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "EventHandler.h"
#include "Playground.h"

#include <chrono>
#include <thread>


enum class GameState {
    RUNNING,
    PAUSE
};


class Game {

public:
    
    Game();
    ~Game();

    void gameLoop();

private:

    void respond(std::vector<Event> events);

    void update();
    void render();
    
    /*
    * Essentials
    */
    int _realFps;
    float _deltaTime;
    bool _running;
    GameState _gameState;
    unsigned int _targetTickRate;
    WindowHandler* _windowHandler;
    EventHandler _eventHandler;

    /*
    * Arcanoid related
    */
    Playground* _playground;
    

    class Time {
    public:

        Time();
        Time(unsigned int const tickRate);

        void wait();

        int _tickPerSec;

    private:
        std::chrono::steady_clock::duration _tickDuration;
        std::chrono::steady_clock::time_point _lastTime;
        std::chrono::steady_clock::duration _secondDuration;
        std::chrono::steady_clock::duration _forTPSCheck;
        int _tickCount;
        
    };


};


#endif