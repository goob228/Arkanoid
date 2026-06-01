#ifndef RECTCOLLIDER_H
#define RECTCOLLIDER_H

#include "Base.h"
#include "SFMLtypes.h"

#include "WindowHandler.h"



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

    virtual void draw(WindowHandler* windowHandler){};

    virtual void bounced(){};

protected:

    bool _onRemove = false;

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


class StrongBlock : public Block {
public:

    StrongBlock(int const posx, int const posy, int const width, int const height);


private:

    int _bouncesCount = 0;
    int _maxBounces = 2;

};

class SpeedBlock : public Block {
public:

    SpeedBlock(int const posx, int const posy, int const width, int const height);

private:

    int _bouncesCount = 0;
    int _maxBounces = 2;

};




#endif
