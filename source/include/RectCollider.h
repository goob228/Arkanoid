#ifndef RECTCOLLIDER_H
#define RECTCOLLIDER_H

//////////////////////////////////////////////////////
//
//  Здесь RectCollider и все виды блоков, наследующие 
//  от RectCollider
//
//////////////////////////////////////////////////////

#include "Base.h"
#include "SFMLtypes.h"

#include "WindowHandler.h"

class Ball;


class RectCollider{

public:
    RectCollider(){};
    RectCollider(int const posx, int const posy, int const width, int const height);

    /*
    * Функция расчета пересечения мячика с центром center, радиусом radius и направлением 
    * движения dir с прямоугольником. На выход дает растояния, через которое столкнется с прямоугольником.
    * Если мячик не пересекает прямоугольник, или если мячик внутри прямоугольника, 
    * или если расстояние больше maxDist (- расстояние на которое мячик должен сдвинуться за кадр)
    * то функция возвращает -1.0f
    */
    float movingCircleIntersectsRect(fVector2& center, fVector2& dir, float maxDist, float radius);

    void sdf(fVector2& center, float& dist);

    void sdfWithNormal(fVector2& center, fVector2& normal, float& dist);

    fVector2 getPos();

    virtual void draw(WindowHandler* windowHandler){};

    virtual void bounced(Ball* ball){};

    bool _onRemove = false;

    int _flag = -1;

protected:

    fVector2 _position;
    fVector2 _scale;

};


class Block : public RectCollider {
public:

    Block(int const posx, int const posy, int const width, int const height);

    void draw(WindowHandler* windowHandler) override;


protected:

    RectangleShape _shape;

};


class RegularBlock : public Block {
public:

    RegularBlock(int const posx, int const posy, int const width, int const height);

    void bounced(Ball* ball) override;

private:

};

class StrongBlock : public Block {
public:

    StrongBlock(int const posx, int const posy, int const width, int const height);

    void bounced(Ball* ball) override;

    int const _maxBounces = 2;

private:

    int _bouncesCount = 0;
    

};

class SpeedBlock : public Block {
public:

    SpeedBlock(int const posx, int const posy, int const width, int const height);

    void bounced(Ball* ball) override;

private:

    float _speedAdd;

};

class BonusBlock : public Block {
public:

    BonusBlock(int const posx, int const posy, int const width, int const height);

    void bounced(Ball* ball) override;

    

};

class MoveableBlock : public Block {
public:

    MoveableBlock(int const posx, int const posy, int const width, int const height, float const boundLeft, float const boundRight);

    void moveLeft(float const dt);

    void moveRight(float const dt);

    void setSpeed(float const speed);

    void setLength(float const length);

    float getSpeed();

    float getLength();

    void bounced(Ball* ball) override;

private:

    float _speed;
    float _boundLeft;
    float _boundRight;

};




#endif
