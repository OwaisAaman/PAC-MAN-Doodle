#ifndef MOVABLE_H
#define MOVABLE_H

#include <SFML/Graphics.hpp>
#include "myApplication.h"

class movable{
    protected:
        sf::Sprite sprite_;
        sf::Texture texture_;
        sf::Vector2f position_;
        bool right_velocity_;
        bool left_velocity_;
        bool up_velocity_;
        bool down_velocity_;
    public:
        movable(myApplication&, const std::string&);
        void move();
        sf::Sprite& getSprite();
};


#endif //MOVABLE_H