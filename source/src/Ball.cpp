#include "Ball.h"

Ball::Ball()
{
    _radius = 10.f;
    _direction = fVector2(-1.f/std::sqrt(2.f),1.f/std::sqrt(2.f));
    _position = fVector2(300.f,300.f);
    _speed = 300.f;

    _shape = CircleShape();
    _shape.setFillColor(Color::White);
    _shape.setRadius(_radius);
    _shape.setPosition(_position);
    
}

fVector2 reflect(fVector2& incident, fVector2& normal) {
    float dotProduct = incident.x * normal.x + incident.y * normal.y;
    return sf::Vector2f(
        incident.x - 2 * dotProduct * normal.x,
        incident.y - 2 * dotProduct * normal.y
    );
}

void Ball::update(float dt, std::vector<std::shared_ptr<RectCollider>> colliders)
{
    _colliderIds.clear();
    float distance = dt*_speed;
    for (int i = 0; i < 5; i++) {
        float best = circleCast(colliders, distance);
        if (best >= 0.0f) {
            for (const auto& id : _colliderIds) {
                distance -= best;
                _position += _direction*best;
                fVector2 normal;
                float sdf;
                colliders[id]->sdfWithNormal(_position, normal, sdf);
                
                _position -= normal*(sdf-_radius-1e-6f);
                _direction = reflect(_direction, normal );
            }
            _colliderIds.clear();
                
        } else {
            _position += _direction*distance;
            break;
        }
    }

    _shape.setPosition(fVector2(_position.x - _radius, _position.y - _radius));
}

void Ball::draw(WindowHandler* windowHandler)
{
    windowHandler->drawCircle(_shape);
}

bool areSimilarAbsolute(float a, float b, float epsilon = 1e-6f) {
    return std::fabs(a - b) <= epsilon;
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

void Ball::circleSdfs(std::vector<std::shared_ptr<RectCollider>> colliders)
{
    for (int i = 0; i < colliders.size(); i++) {
        fVector2 normal;
        float sdf;
        colliders[i]->sdfWithNormal(_position, normal, sdf);
        if (sdf < _radius) {
            fVector2 deriv = normal*(-sdf+_radius);
            _position -= deriv;
            std::cout << "sdf moved x: " << deriv.x << "  y: " << deriv.y << std::endl;
        } else {
            std::cout << "skip sdf" << std::endl;
        }

    }
}