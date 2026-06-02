#include "Game.h"

Game::Game()
{
    int width = 750;
    int height = 800;

    _running = false;
    _targetTickRate = 120;
    _windowHandler = new WindowHandler(width, height);
    _playground = new Playground(0, height-width, width, width);
}

Game::~Game()
{
    delete _windowHandler;
    _windowHandler = nullptr;

    delete _playground;
    _playground = nullptr;
}


void Game::respond(std::vector<Event> events)
{
    for (const auto& event : events) {
        switch (event) {
            case Event::CLOSE_WINDOW:
                _running = false;
                break;
            case Event::CLICK_MOUSE:
                if (_gameState == GameState::RUNNING) {
                    iVector2 mousePos = EventHandler::getMousePos(_windowHandler);
                }
                break;
            case Event::CLICK_ESC:
                _gameState = (_gameState == GameState::RUNNING) ? GameState::PAUSE : GameState::RUNNING;
                break;
            case Event::LEFT_PRESSED:
                _playground->_carriage->moveLeft(_deltaTime);
                break;
            case Event::RIGHT_PRESSED:
                _playground->_carriage->moveRight(_deltaTime);
                break;
        }
    }
    _eventHandler._events.clear();
}




void Game::gameLoop()
{   
    Time time(_targetTickRate);
    _running = true;
    _gameState = GameState::RUNNING;
    _deltaTime = 1.f/float(_targetTickRate);
    
    _playground->initialize();

    while (_running) {
        _eventHandler.handleEvents(_windowHandler);
        respond(_eventHandler._events);

        if (_gameState == GameState::RUNNING) update();

        render();
        time.wait();
        _realFps = time._tickPerSec;
    }
}

void Game::update()
{
    _playground->update(_deltaTime);
}  

void Game::render()
{
    _windowHandler->fill(GameColor::Gray);
    std::string mytxt = "Lives: " + std::to_string(_playground->_lives);
    _windowHandler->drawText(mytxt,{10.f,10.f});

    _playground->draw(_windowHandler);

    _windowHandler->display();
}   



Game::Time::Time()
{
    int tickRate = 60;
    _tickDuration = std::chrono::milliseconds(1000 / tickRate);
    _lastTime = std::chrono::steady_clock::now();
    _secondDuration = std::chrono::milliseconds(1000);
    _forTPSCheck = std::chrono::milliseconds(0);
    _tickCount = 0;
    _tickPerSec = 0;
}

Game::Time::Time(unsigned int const tickRate)
{
    THROW_IF_ZERO(tickRate);
    _tickDuration = std::chrono::milliseconds(1000 / tickRate);
    _lastTime = std::chrono::steady_clock::now();
    _secondDuration = std::chrono::milliseconds(1000);
    _forTPSCheck = std::chrono::milliseconds(0);
    _tickCount = 0;
    _tickPerSec = 0;
}

void Game::Time::wait()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - _lastTime;
    
    _forTPSCheck += elapsed;
    
    _tickCount++;
    if (_forTPSCheck > _secondDuration){
        _tickPerSec = _tickCount;
        _tickCount = 0;
        _forTPSCheck = std::chrono::milliseconds(0);
    }
    
    
    if (elapsed < _tickDuration) {
        std::this_thread::sleep_for(_tickDuration - elapsed);
    }    

    _lastTime = std::chrono::steady_clock::now();
}