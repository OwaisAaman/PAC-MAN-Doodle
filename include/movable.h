#ifndef MOVABLE_H
#define MOVABLE_H

#include <SFML/Graphics.hpp>
#include "myApplication.h"
#include "tileMap.h"

class movable{
    protected:
        tileMap map_;
        sf::Sprite sprite_;
        sf::Texture texture_;
        sf::Vector2f position_;
        bool right_velocity_;
        bool left_velocity_;
        bool up_velocity_;
        bool down_velocity_;
    public:
        movable();
        movable(myApplication&, const std::string&, const std::string&);
        void move();
        void setMap(myApplication&, const std::string&);
        sf::Sprite& getSprite();
        int getIndexFromPosition();
        void setVelocity(const std::string&);
        void killVelocity(const std::string&);
        void setTexture(myApplication&, const std::string&);
};


#endif //MOVABLE_H