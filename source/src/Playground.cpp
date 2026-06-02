#include "Playground.h"




Playground::Playground(int const posx, int const posy, int const width, int const height)
{
    _posx = posx;
    _posy = posy;
    _width = width;
    _height = height;
    _playgroundShape = RectangleShape();
    _playgroundShape.setSize(fVector2(float(_width), float(_height)));
    _playgroundShape.setPosition(float(_posx),float(_posy));
    _playgroundShape.setFillColor(GameColor::Black);

    _boundsPlayground = std::make_shared<RectCollider>(posx-50, posy-50, width+100, height+100);
}

Playground::~Playground()
{
}

void Playground::initialize() 
{
    _placedTexts.clear();
    _balls.clear();
    _bonuses.clear();
    _blocks.clear();
    int width = _width/(_countx+2); //block width
    int height = _height/(_county*3); //block height

    for (int i = 0+1; i < _countx+1; i++) {
        for (int e = 0+1; e < _county+1; e++) {
            int x = i*width+_posx;
            int y = e*height+_posy;

            
            std::uniform_int_distribution<> typeDistribution(0, 10);

            int blockType = typeDistribution(Base::generator);

            if (blockType <= 0) {
                _blocks.push_back(std::make_shared<Block>(x, y, width, height));
            } else if (blockType <= 2) {
                _blocks.push_back(std::make_shared<RegularBlock>(x, y, width, height));
            } else if (blockType <= 8) {
                _blocks.push_back(std::make_shared<BonusBlock>(x, y, width, height));
            } else if (blockType <= 9) {
                _blocks.push_back(std::make_shared<StrongBlock>(x, y, width, height));
            } else if (blockType <= 10) {
                _blocks.push_back(std::make_shared<SpeedBlock>(x, y, width, height));
            } 
        }
    }


    // top
    _blocks.push_back(std::make_shared<RectCollider>(_posx+0, _posy-height, _width, height));

    // left
    _blocks.push_back(std::make_shared<RectCollider>(_posx-width, _posy+0, width, _height));

    // right
    _blocks.push_back(std::make_shared<RectCollider>(_posx+_width, _posy+0, width, _height));


    // carriage каретка

    _carriage = new MoveableBlock(_posx + _width/2-width, _posy + _height - 4*height, 2*width, height, float(_posx), float(_posx+_width));
    std::shared_ptr<RectCollider> sharedptr(_carriage);
    _blocks.push_back(sharedptr);

    // lives
    _lives = 3;

    // ball

    addBall();

}

void Playground::addBall()
{
    auto ball = std::make_unique<Ball>(_posx+_width/2, _posy+_height/2);
    ball->setBoundsCollider(_boundsPlayground);
    _balls.push_back(std::move(ball));
}

void Playground::addBonus(int const posx, int const posy)
{
    std::uniform_int_distribution<> typeDistribution(0, 5);
    int bonusType = typeDistribution(Base::generator);


    if (bonusType == 0) {
        auto bonus = std::make_unique<BallBonus>(posx, posy);
        bonus->setBoundsCollider(_boundsPlayground);
        _bonuses.push_back(std::move(bonus));
    } else if (bonusType == 1) {
        auto bonus = std::make_unique<BottomBonus>(posx, posy);
        bonus->setBoundsCollider(_boundsPlayground);
        _bonuses.push_back(std::move(bonus));
    } else if (bonusType == 2) {
        auto bonus = std::make_unique<CarriageSpeedBonus>(posx, posy);
        bonus->setBoundsCollider(_boundsPlayground);
        _bonuses.push_back(std::move(bonus));
    } else if (bonusType == 3) {
        auto bonus = std::make_unique<CarriageLengthBonus>(posx, posy);
        bonus->setBoundsCollider(_boundsPlayground);
        _bonuses.push_back(std::move(bonus));
    } else if (bonusType == 4) {
        auto bonus = std::make_unique<BallDirBonus>(posx, posy);
        bonus->setBoundsCollider(_boundsPlayground);
        _bonuses.push_back(std::move(bonus));
    } else if (bonusType == 5) {
        auto bonus = std::make_unique<BallSpeedBonus>(posx, posy);
        bonus->setBoundsCollider(_boundsPlayground);
        _bonuses.push_back(std::move(bonus));
    }
    
}

void Playground::addPlacedText(std::string const & txt, fVector2 const pos)
{
    auto placedtext = std::make_unique<PlacedText>(txt, pos);
    _placedTexts.push_back(std::move(placedtext));
}

void Playground::checkCarriageBonuses()
{
    for (const auto& bonus : _bonuses) {
        float dist;
        _carriage->sdf(bonus->_position, dist);
        if (dist-bonus->_radius < 0.0f) {
            if (!bonus->_onRemove) addPlacedText(bonus->_name, bonus->_position);
            bonus->touched(this);
            
        }
    }
}


void Playground::update(float const dt)
{

    //////////////// мячи
    if (_lives == 0) {
        initialize();
    }
    
    for (auto it = _balls.begin(); it != _balls.end(); ) {
        if ((*it)->_onRemove) {
            it = _balls.erase(it); 
        } else {
            (*it)->update(dt, _blocks);
            ++it;
        }
    }

    if (_balls.size() == 0) {
        _lives -= 1;
        addBall();
    }
    ///////////// блоки

    for (auto it = _blocks.begin(); it != _blocks.end(); ) {
        if ((*it)->_onRemove) {
            if ((*it)->_flag == 1) {
                fVector2 itspos = (*it)->getPos();
                addBonus(int(itspos.x), int(itspos.y));
            } else if ((*it)->_flag == 2) {
                _lives++;
            }
            it = _blocks.erase(it); 
        } else {
            ++it;
        }
    }

    checkCarriageBonuses();

    ///////////// бонусы

    for (auto it = _bonuses.begin(); it != _bonuses.end(); ) {
        if ((*it)->_onRemove) {
            it = _bonuses.erase(it); 
        } else {
            (*it)->update(dt);
            ++it;
        }
    }

    //////////// тексты
    
    for (auto it = _placedTexts.begin(); it != _placedTexts.end(); ) {
        if ((*it)->_onRemove) {
            
            it = _placedTexts.erase(it); 
        } else {
            (*it)->update();
            ++it;
        }
    }

}

void Playground::draw(WindowHandler* windowHandler) 
{
    windowHandler->drawSquare(_playgroundShape);

    for (int i = 0; i < _blocks.size(); i++)
    {
        _blocks[i]->draw(windowHandler);
    }

    for (const auto& ball : _balls) {
        ball->draw(windowHandler);
    }
    

    for (const auto& bonus : _bonuses) {
        bonus->draw(windowHandler);
    }

    for (const auto& placedtext : _placedTexts) {
        placedtext->draw(windowHandler);
    }

}