#include "RectCollider.h"
#include "Ball.h"

RectCollider::RectCollider(int const posx, int const posy, int const width, int const height)
{

    _position = fVector2(float(posx+width/2),float(posy+height/2));
    _scale = fVector2(float(width/2),float(height/2));

}


fVector2 RectCollider::getPos()
{
    return _position;
}

// Основная функция проверки движущегося круга
float RectCollider::movingCircleIntersectsRect(fVector2& center, fVector2& dir, float maxDist, float radius)
{
    if (_onRemove) return -1.0f;

    // Переводим прямоугольник в центрированные координаты (центр в 0)
    float cx = _position.x;
    float cy = _position.y;
    fVector2 size = { _scale.x, _scale.y };
    fVector2 ro = { center.x - cx, center.y - cy };
    fVector2 rd = dir;   // предполагается нормированным

    fVector2 m = fVector2(1.f/rd.x, 1.f/rd.y);
    fVector2 n = fVector2(m.x*ro.x, m.y * ro.y);
    fVector2 k = fVector2(std::fabs(m.x) * (size.x + radius), std::fabs(m.y) * (size.y + radius));
    fVector2 t1 = fVector2(-n.x - k.x, -n.y - k.y);
    fVector2 t2 = fVector2(-n.x + k.x, -n.y + k.y);
    float tN = std::max(t1.x, t1.y);
    float tF = std::max(t2.x, t2.y);
    if (tN > tF || tF < 0.0f) return -1.0f;
    float t = tN;


    // ----- 2. Преобразование в первый квадрант (все координаты неотрицательны) -----
    fVector2 pos = { ro.x + rd.x * t, ro.y + rd.y * t };
    fVector2 s = { (pos.x >= 0.0f) ? 1.0f : -1.0f, (pos.y >= 0.0f) ? 1.0f : -1.0f };
    ro.x *= s.x; rd.x *= s.x;
    ro.y *= s.y; rd.y *= s.y;
    pos.x *= s.x; pos.y *= s.y;

    // ----- 3. Проверка попадания внутрь основного прямоугольника (без скругления) -----

    if (pos.x <= size.x && pos.y <= size.y) {
        return t;   // пересечение произошло с гранью/внутренностью
    }

    // ----- 4. Подготовка для квадратных уравнений (угол size) -----
    fVector2 oc = { ro.x - size.x, ro.y - size.y };   // вектор от угла до начала луча
    fVector2 dd = { rd.x * rd.x, rd.y * rd.y };
    fVector2 oo = { oc.x * oc.x, oc.y * oc.y };
    fVector2 od = { oc.x * rd.x, oc.y * rd.y };
    float ra2 = radius * radius;

    t = std::numeric_limits<float>::max();

    // 4a) Угол (окружность радиуса radius вокруг угла (size.x, size.y))
    {
        float b = od.x + od.y;
        float c = oo.x + oo.y - ra2;
        float h = b*b - c;
        if (h > 0.0f) t = -b - std::sqrt(h);
    }

    // 4b) Ребро X (горизонтальная сторона: капсула вдоль X с радиусом radius)
    {

        float a = dd.y;
        float b = od.y;
        float c = oo.y - ra2;
        float h = b * b - a * c;
        if (h > 0.0f) {
            h = (-b - std::sqrt(h)) / a;
            if (h > 0.0f && h < t && std::fabs(ro.x + rd.x*h) < size.x) t = h;
        }
    }

    // 4c) Ребро Y (вертикальная сторона: капсула вдоль Y)
    {
        float a = dd.x;
        float b = od.x;
        float c = oo.x - ra2;
        float h = b*b - a*c;
        if (h>0.0f) {
            h = (-b-std::sqrt(h))/a;
            if (h>0.0f && h<t && std::fabs(ro.y+rd.y*h) < size.y) t = h;
        }
    }

    if (t > std::numeric_limits<float>::max() || t > maxDist)
        return -1.0f;


    return t;
}

void RectCollider::sdf(fVector2& center, float& dist)
{
    fVector2 w = fVector2(std::fabs(_position.x-center.x)-_scale.x, 
        std::fabs(_position.y-center.y)-_scale.y);
    fVector2 s = fVector2((_position.x-center.x)<0.0f ? -1.f : 1.f, 
        (_position.y-center.y)<0.0f ? -1.f : 1.f);

    float g = std::max(w.x, w.y);
    fVector2 q = fVector2(std::max(w.x,0.f),std::max(w.y,0.f));
    float l = std::sqrt(q.x*q.x + q.y*q.y);
    //OUT
    dist = (g>0.0f) ? l : g;
}

void RectCollider::sdfWithNormal(fVector2& center, fVector2& normal, float& dist)
{
    fVector2 w = fVector2(std::fabs(_position.x-center.x)-_scale.x, 
        std::fabs(_position.y-center.y)-_scale.y);

    fVector2 s = fVector2((_position.x-center.x)<0.0f ? 1.f : -1.f, 
        (_position.y-center.y)<0.0f ? 1.f : -1.f);

    float g = std::max(w.x, w.y);
    fVector2 q = fVector2(std::max(w.x,0.f),std::max(w.y,0.f));
    float l = std::sqrt(q.x*q.x + q.y*q.y);
    //OUT
    dist = (g>0.0f) ? l : g;
    normal = fVector2(s.x * ((g > 0.0f) ? (q.x / l) : ((w.x > w.y) ? 1.0f : 0.0f)),  
        s.y * ((g > 0.0f) ? (q.y / l) : ((w.x > w.y) ? 0.0f : 1.0f)));
}

//////////////////////////////////////////////


Block::Block(int const posx, int const posy, int const width, int const height) : RectCollider(posx, posy, width, height)
{
    _shape = RectangleShape();
    _shape.setPosition(fVector2(float(posx), float(posy)));
    _shape.setSize(fVector2(float(width), float(height)));
    _shape.setFillColor(Color(120, 120, 120, 255));

}

void Block::draw(WindowHandler* windowHandler)
{
    if(_onRemove) return;
    windowHandler->drawSquare(_shape);
}

//////////////////////////////////////////////

RegularBlock::RegularBlock(int const posx, int const posy, int const width, int const height) : Block(posx, posy, width, height)
{
    _shape.setFillColor(GameColor::White);
}

void RegularBlock::bounced(Ball* ball)
{
    if(_onRemove) return;
    _onRemove = true;
}

//////////////////////////////////////////////

StrongBlock::StrongBlock(int const posx, int const posy, int const width, int const height) : Block(posx, posy, width, height)
{
    _shape.setFillColor(GameColor::Green);

    _flag = 2;
}

void StrongBlock::bounced(Ball* ball) 
{
    if(_onRemove) return;
    _bouncesCount++;
    if (_bouncesCount >= _maxBounces) {
        _onRemove = true;
    }
}

//////////////////////////////////////////////

SpeedBlock::SpeedBlock(int const posx, int const posy, int const width, int const height) : Block(posx, posy, width, height)
{
    _shape.setFillColor(GameColor::Red);

    _speedAdd = 100.0f;
}

void SpeedBlock::bounced(Ball* ball)
{
    if(_onRemove) return;
    ball->addSpeed(_speedAdd);
    _onRemove = true;
}

//////////////////////////////////////////////

BonusBlock::BonusBlock(int const posx, int const posy, int const width, int const height) : Block(posx, posy, width, height)
{
    _shape.setFillColor(GameColor::Blue);

    _flag = 1;

}

void BonusBlock::bounced(Ball* ball)
{
    if(_onRemove) return;
    _onRemove = true;
}

//////////////////////////////////////////////

MoveableBlock::MoveableBlock(int const posx, int const posy, int const width, int const height, float const boundLeft, float const boundRight) 
: Block(posx, posy, width, height)
{
    _shape.setFillColor(GameColor::Magenta);
    _speed = 300.0f;
    _boundLeft = boundLeft;
    _boundRight = boundRight;
}

void MoveableBlock::moveLeft(float const dt)
{
    _position.x -= _speed*dt;
    _position.x = std::clamp(_position.x, _boundLeft+_scale.x, _boundRight-_scale.x);

    _shape.setPosition(_position-_scale);
}

void MoveableBlock::moveRight(float const dt)
{
    _position.x += _speed*dt;
    _position.x = std::clamp(_position.x, _boundLeft+_scale.x, _boundRight-_scale.x);
    _shape.setPosition(_position-_scale);
}

void MoveableBlock::setSpeed(float const speed)
{
    _speed = speed;
}

void MoveableBlock::setLength(float const length)
{
    _scale.x = length;
    _shape.setSize(_scale*2.0f);
    _shape.setPosition(_position-_scale);
}

float MoveableBlock::getSpeed()
{
    return _speed;
}

float MoveableBlock::getLength()
{
    return _scale.x;
}

void MoveableBlock::bounced(Ball* ball)
{
    float factor = (ball->_position.x - _position.x)/(4.0f*_scale.x);
    ball->addDirection(fVector2(factor, 0.0f));
}