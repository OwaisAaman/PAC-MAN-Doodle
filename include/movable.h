#ifndef MOVABLE_H
#define MOVABLE_H

#include <SFML/Graphics.hpp>
#include "tileMap.h"

//base class for pacman and the ghosts

class myApplication;

class movable{
    protected:
        sf::Sprite sprite_;
        sf::Vector2f position_;
        bool right_velocity_;
        bool left_velocity_;
        bool up_velocity_;
        bool down_velocity_;
        bool is_active_;
        bool is_alive_;
    public:
        movable();
        movable(const std::vector <int>&, const tileMap&, const std::string&, const myApplication&, const bool, const int);
        int getRandomSpawn(const std::vector <int>&);
        sf::Vector2f getPositionFromIndex(const int, const tileMap&);
        int getIndexFromPosition(const tileMap&);
        void setVelocity(const std::string&);
        void move(const tileMap&, const std::vector <int>&);
        void setPosition(const sf::Vector2f);
        void killVelocity(const std::string&);
        void killAllVelocity();
        void setTexture(const myApplication&, const std::string&);
        void updateActiveStatus();
        sf::Sprite& getSprite();
        sf::Vector2f getPosition();
        const bool getActiveStatus();
        const bool getAliveStatus();
};

#endif //MOVABLE_H