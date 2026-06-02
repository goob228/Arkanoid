#include "Ball.h"

#define TORADIANS(value)  value*0.01745329251f

Ball::Ball(int const posx, int const posy)
{
    _radius = 10.f;
    _position = fVector2(float(posx), float(posy));
    _speed = 300.f;

    setRandomDirection();

    _shape = CircleShape();
    _shape.setFillColor(Color::White);
    _shape.setRadius(_radius);
    _shape.setPosition(fVector2(_position.x - _radius, _position.y - _radius));
    
}

void Ball::addSpeed(float const addspeed)
{
    _speed += addspeed;
}

bool areSimilarAbsolute(float a, float b, float epsilon = 1e-6f) {
    return std::fabs(a - b) <= epsilon;
}

void Ball::addDirection(fVector2 const ddir)
{
    _direction += ddir;
    float length = std::sqrt(_direction.x * _direction.x + _direction.y * _direction.y);
    if (areSimilarAbsolute(length, 0.0f)) {
        setRandomDirection();
    } else {
        _direction /= length;
    }
}

void Ball::setBoundsCollider(std::shared_ptr<RectCollider> boundsCollider) 
{
    _boundsCollider = boundsCollider;
}

void Ball::setRandomDirection()
{
    std::uniform_int_distribution<> typeDistribution(210, 330);
    int angle = typeDistribution(Base::generator);
    float rad = TORADIANS(float(angle)); 
    _direction = fVector2(std::cos(rad),std::sin(rad));
}

fVector2 reflect(fVector2& incident, fVector2& normal) {
    float dotProduct = incident.x * normal.x + incident.y * normal.y;
    return sf::Vector2f(
        incident.x - 2 * dotProduct * normal.x,
        incident.y - 2 * dotProduct * normal.y
    );
}

void Ball::update(float const dt, std::vector<std::shared_ptr<RectCollider>> colliders)
{
    _colliderIds.clear();
    float distance = dt*_speed;
    for (int i = 0; i < 5; i++) {
        float best = circleCast(colliders, distance);
        if (best >= 0.0f) {
            bool made = false;
            for (const auto& id : _colliderIds) {
                distance -= best;
                _position += _direction*best;
                fVector2 normal;
                float sdf;
                colliders[id]->sdfWithNormal(_position, normal, sdf);
                _position -= normal*(sdf-_radius-1e-6f);
                if (!made) _direction = reflect(_direction, normal );
                made = true;
                colliders[id]->bounced(this);
            }
            _colliderIds.clear();
                
        } else {
            _position += _direction*distance;
            break;
        }
    }

    _shape.setPosition(fVector2(_position.x - _radius, _position.y - _radius));

    checkOutOfBounds();
}

void Ball::draw(WindowHandler* windowHandler)
{
    windowHandler->drawCircle(_shape);
}

float Ball::circleCast(std::vector<std::shared_ptr<RectCollider>> colliders, float distance)
{
    
    float best = -1.0f;
    for (int i = 0; i < colliders.size(); i++) {
        float dist = colliders[i]->movingCircleIntersectsRect(_position, _direction, distance, _radius);
        if (dist >= 0.0f) {

            if (best < -0.1f) {
                best = dist;
                _colliderIds.push_back(i);
            } else {
                if (areSimilarAbsolute(dist, best)) {
                    _colliderIds.push_back(i);
                } else if (dist < best) {
                    best = dist;
                    _colliderIds.clear();
                    _colliderIds.push_back(i);
                }
            }
        }
    }

    return best;
}


void Ball::checkOutOfBounds()
{
    if (_boundsCollider) {
        float dist;
        _boundsCollider->sdf(_position, dist);

        if (dist - _radius > 0.0f) _onRemove=true;
    }
}