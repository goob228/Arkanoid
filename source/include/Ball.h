#ifndef BALL_H
#define BALL_H

//////////////////////////////////////////////////////
//
//  Здесь Ball - мячик
//
//////////////////////////////////////////////////////

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "RectCollider.h"



class Ball{

friend class MoveableBlock;

public:

    Ball(int const posx, int const posy);

    void update(float const dt, std::vector<std::shared_ptr<RectCollider>> colliders);

    void draw(WindowHandler* windowHandler);

    void addSpeed(float const addspeed);    

    void addDirection(fVector2 const ddir);  

    void setBoundsCollider(std::shared_ptr<RectCollider> boundsCollider);

    void setRandomDirection();

    bool _onRemove = false;

private:

    void checkOutOfBounds();

    float circleCast(std::vector<std::shared_ptr<RectCollider>> colliders, float distance);



    float _radius;
    float _speed;
    fVector2 _direction;
    fVector2 _position;
    
    std::vector<int> _colliderIds;

    std::shared_ptr<RectCollider> _boundsCollider;

    CircleShape _shape;

};

#endif