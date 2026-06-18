#include "Bonus.h"
#include "Playground.h"


PlacedText::PlacedText(std::string const & txt, fVector2 pos)
{
    _txt = txt;
    _pos = pos;

}

void PlacedText::update()
{
    if (_onRemove) return;
    _pos.y -= 1.0f;
    _animCount++;
    if (_animCount >= _animDead) {
        _onRemove = true;
    }
}

void PlacedText::draw(WindowHandler* windowHandler)
{
    if (_onRemove) return;
    windowHandler->drawText(_txt,_pos);
}


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
    _shape.setFillColor(GameColor::Yellow);
    _name += "+1 ball";
}

void BallBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    playground->addBall();
    _onRemove = true;
}

//////////////////////////////////////////////
BallSpeedBonus::BallSpeedBonus(int const posx, int const posy) : Bonus(posx, posy)
{
    _shape.setFillColor(GameColor::Red);
    _name += "+ ball speed";
}

void BallSpeedBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    if (playground->_balls.size() >= 1) {
        if (playground->_balls[0]) {
            playground->_balls[0]->addSpeed(_speedAdd);
        }
    }
    
    _onRemove = true;
}

//////////////////////////////////////////////
BallDirBonus::BallDirBonus(int const posx, int const posy) : Bonus(posx, posy)
{
    _shape.setFillColor(GameColor::Orange);
    _name += "random ball direction";
}

void BallDirBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    if (playground->_balls.size() >= 1) {
        if (playground->_balls[0]) {
            playground->_balls[0]->setRandomDirection();
        }
    }
    
    _onRemove = true;
}


//////////////////////////////////////////////
BottomBonus::BottomBonus(int const posx, int const posy) : Bonus(posx, posy)
{
    _shape.setFillColor(GameColor::Magenta);
    _name += "+ temporary bottom";
}

void BottomBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    fVector2 carpos = playground->_carriage->getPos();
    carpos.x = float(playground->_posx);
    playground->_blocks.push_back(std::make_shared<RegularBlock>(int(carpos.x), int(carpos.y), playground->_width, 60));

    _onRemove = true;
}


//////////////////////////////////////////////
CarriageSpeedBonus::CarriageSpeedBonus(int const posx, int const posy) : Bonus(posx, posy)
{
    _shape.setFillColor(GameColor::Cyan);
    _name += "+ carriage speed";
}

void CarriageSpeedBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    float speed = playground->_carriage->getSpeed();
    speed += 20.0f;
    playground->_carriage->setSpeed(speed);
    _onRemove = true;
}


//////////////////////////////////////////////
CarriageLengthBonus::CarriageLengthBonus(int const posx, int const posy) : Bonus(posx, posy)
{
    _shape.setFillColor(GameColor::Green);
    _name += "+ carriage length";
}

void CarriageLengthBonus::touched(Playground* playground)
{
    if (_onRemove) return;
    float length = playground->_carriage->getLength();
    length += 10.0f;
    playground->_carriage->setLength(length);
    _onRemove = true;
}