#ifndef GAME_H
#define GAME_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "EventHandler.h"

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
    bool _running;
    GameState _gameState;
    unsigned int _targetTickRate;
    WindowHandler* _windowHandler;
    EventHandler _eventHandler;


    
    

    class Time {
    public:

        Time();
        Time(unsigned int const tickRate);

        void wait();

    private:
        std::chrono::steady_clock::duration _tickDuration;
        std::chrono::steady_clock::time_point _lastTime;
        std::chrono::steady_clock::duration _secondDuration;
        std::chrono::steady_clock::duration _forTPSCheck;
        int _tickCount;
        int _tickPerSec;
    };


};


#endif