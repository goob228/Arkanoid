#ifndef BONUS_H
#define BONUS_H

//////////////////////////////////////////////////////
//
//  Здесь Bonus и все виды бонусов, наследующие 
//  от Bonus. Плюс еще есть PlacedText 
//  который нужен просто чтоб писать на экране
//  какой бонус выпал
//
//////////////////////////////////////////////////////

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "RectCollider.h"


class PlacedText{
public:

    PlacedText(std::string const & txt, fVector2 pos);

    void update();

    void draw(WindowHandler* windowHandler);

    std::string _txt;
    fVector2 _pos;

    bool _onRemove = false;

private:

    int _animCount = 0;
    int const _animDead = 100;
    

};


class Playground;

class Bonus {

public:
    Bonus(int const posx, int const posy);

    void draw(WindowHandler* windowHandler);

    void update(float const dt);

    void setBoundsCollider(std::shared_ptr<RectCollider> boundsCollider);

    virtual void touched(Playground* playground){};

    std::string _name = "";

    bool _onRemove = false;

    float _radius;
    float _speed;

    fVector2 _position;

protected:

    CircleShape _shape;

    std::shared_ptr<RectCollider> _boundsCollider;

private:

    void checkOutOfBounds();

};

//// Бонус который добавляет шарик

class BallBonus : public Bonus {
public:

    BallBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

};


//// Бонус который добавляет скорости шарику

class BallSpeedBonus : public Bonus {
public:

    BallSpeedBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

    float const _speedAdd = 100.0f;

};


//// Бонус который меняет направление шарика

class BallDirBonus : public Bonus {
public:

    BallDirBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

};


//// Бонус который добавляет дно

class BottomBonus : public Bonus {
public:

    BottomBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

};


//// Бонус который увеличивает скорость каретки

class CarriageSpeedBonus : public Bonus {
public:

    CarriageSpeedBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

};


//// Бонус который увеличивает длину каретки

class CarriageLengthBonus : public Bonus {
public:

    CarriageLengthBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

};


#endif