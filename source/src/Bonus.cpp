#include "Bonus.h"
#include "Playground.h"


Bonus::Bonus(int const posx, int const posy)
{
    _radius = 6.f;
    _position = fVector2(float(posx), float(posy));
    _speed = 100.f;

    _shape = CircleShape();
    _shape.setRadius(_radius);
    _shape.setPosition(fVector2(_position.x - _radius, _position.y - _radius));
}

void Bonus::draw(WindowHandler* windowHandler)
{
    if (_onRemove) return;
    windowHandler->drawCircle(_shape);
}

void Bonus::update(float const dt)
{
    _position.y += _speed*dt;
    _shape.setPosition(fVector2(_position.x - _radius, _position.y - _radius));
    checkOutOfBounds();
}

void Bonus::setBoundsCollider(std::shared_ptr<RectCollider> boundsCollider) 
{
    _boundsCollider = boundsCollider;
}

void Bonus::checkOutOfBounds()
{
    if (_boundsCollider) {
        float dist;
        _boundsCollider->sdf(_position, dist);

        if (dist - _radius > 0.0f) _onRemove=true;
    }
}


//////////////////////////////////////////////

BallBonus::BallBonus(int const posx, int const posy) : Bonus(posx, posy)
{
    _shape.setFillColor(Color::Yellow);
}

void BallBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    playground->addBall();
    _onRemove = true;
}


//////////////////////////////////////////////

BottomBonus::BottomBonus(int const posx, int const posy) : Bonus(posx, posy)
{
    _shape.setFillColor(Color::Magenta);
}

void BottomBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    fVector2 carpos = playground->_carriage->getPos();
    carpos.x = float(playground->_posx);
    playground->_blocks.push_back(std::make_shared<RegularBlock>(int(carpos.x), int(carpos.y), playground->_width, 60));

    _onRemove = true;
}