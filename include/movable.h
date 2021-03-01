#ifndef MOVABLE_H
#define MOVABLE_H

#include <SFML/Graphics.hpp>
#include "tileMap.h"

class myApplication;

class movable{
    protected:
        sf::Sprite sprite_;
        sf::Texture texture_;
        sf::Vector2f position_;
        bool right_velocity_;
        bool left_velocity_;
        bool up_velocity_;
        bool down_velocity_;
        bool is_active_;
    public:
        movable();
        movable(std::vector <int>&, tileMap&, const std::string&, myApplication&, bool, int);
        int getRandomSpawn(std::vector <int>&);
        void move(tileMap&, std::vector <int>&);
        sf::Vector2f getPositionFromIndex(int, tileMap&);
        sf::Sprite& getSprite();
        int getIndexFromPosition(tileMap&);
        void setVelocity(const std::string&);
        void killVelocity(const std::string&);
        void setTexture(myApplication&, const std::string&);
        bool getActiveStatus();
};


#endif //MOVABLE_H