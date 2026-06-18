#ifndef PLAYGROUND_H
#define PLAYGROUND_H

//////////////////////////////////////////////////////
//
//  Основная логика игры и взаимодействия находится тут
//
//////////////////////////////////////////////////////

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "Ball.h"
#include "RectCollider.h"
#include "Bonus.h"


class Playground{

friend class BallBonus;
friend class BottomBonus;
friend class BallDirBonus;
friend class BallSpeedBonus;


public:

    Playground(int const posx, int const posy, int const width, int const height);
    ~Playground();

    void initialize();

    void update(float const dt);

    void draw(WindowHandler* windowHandler);

    int _lives;

    MoveableBlock* _carriage;

private:

    void addBall();

    void addBonus(int const posx, int const posy);

    void addPlacedText(std::string const & txt, fVector2 const pos);
    
    void checkCarriageBonuses();

    int const _countx = 10;
    int const _county = 10;
    

    int _posx;
    int _posy;
    int _width;
    int _height;

    std::vector<std::unique_ptr<PlacedText>> _placedTexts;
    std::vector<std::unique_ptr<Ball>> _balls;
    std::vector<std::unique_ptr<Bonus>> _bonuses;
    std::vector<std::shared_ptr<RectCollider>> _blocks;


    std::shared_ptr<RectCollider> _boundsPlayground;

    RectangleShape _playgroundShape;


};


#endif