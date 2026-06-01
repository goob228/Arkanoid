#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "Ball.h"
#include "RectCollider.h"


class Playground{

    friend class Game;

public:

    Playground(int const posx, int const posy, int const width, int const height);
    ~Playground();

    void update(float dt);

    void draw(WindowHandler* windowHandler);

private:

    

    int _posx;
    int _posy;
    int _width;
    int _height;

    Ball _ball;
    std::vector<std::shared_ptr<RectCollider>> _blocks;

    RectangleShape _playgroundShape;


};


#endif