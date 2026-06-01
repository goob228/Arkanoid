#ifndef BONUS_H
#define BONUS_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "RectCollider.h"

class Playground;

class Bonus {

public:
    Bonus(int const posx, int const posy);

    void draw(WindowHandler* windowHandler);

    void update(float const dt);

    void setBoundsCollider(std::shared_ptr<RectCollider> boundsCollider);

    virtual void touched(Playground* playground){};

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

class BallBonus : public Bonus {
public:

    BallBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

};

class BottomBonus : public Bonus {
public:

    BottomBonus(int const posx, int const posy);

    void touched(Playground* playground) override;

};



#endif