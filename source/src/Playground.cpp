#include "Playground.h"




Playground::Playground(int const posx, int const posy, int const width, int const height)
{
    _posx = posx;
    _posy = posy;
    _width = width;
    _height = height;
    _playgroundShape = RectangleShape();
    _playgroundShape.setSize(fVector2(float(_width), float(_height)));
    _playgroundShape.setPosition(float(_posx),float(_posy));
    _playgroundShape.setFillColor(GameColor::Black);

    _blocks.push_back(std::make_shared<Block>(100, 100, 100, 300));
    _blocks.push_back(std::make_shared<Block>(200, 400, 100, 400));
    _blocks.push_back(std::make_shared<Block>(102, 398, 100, 400));
}

Playground::~Playground()
{
}



void Playground::update(float dt)
{
    
    _ball.update(dt, _blocks);
}

void Playground::draw(WindowHandler* windowHandler) 
{
    windowHandler->drawSquare(_playgroundShape);

    _ball.draw(windowHandler);
    

    for (int i = 0; i < _blocks.size(); i++)
    {
        _blocks[i]->draw(windowHandler);
    }

}