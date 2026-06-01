#ifndef BALL_H
#define BALL_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "RectCollider.h"



class Ball{

    friend class Playground;
    
    friend class Game;

public:

    Ball();

    void update(float dt, std::vector<std::shared_ptr<RectCollider>> colliders);

    void draw(WindowHandler* windowHandler);


private:

    float circleCast(std::vector<std::shared_ptr<RectCollider>> colliders, float distance);

    void circleSdfs(std::vector<std::shared_ptr<RectCollider>> colliders);

    float _radius;
    float _speed;
    fVector2 _direction;
    fVector2 _position;
    
    std::vector<int> _colliderIds;

    CircleShape _shape;

};

#endif