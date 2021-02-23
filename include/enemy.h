#ifndef ENEMY_H
#define ENEMY_H

#include "myApplication.h"
#include "movable.h"

class enemy : public movable{
    private:
        int velocity_factor_;
    public:
        enemy();
        enemy(std::vector <int>&, tileMap&, const std::string&, myApplication&);
        enemy(std::vector <int>&, tileMap&, const std::string&, myApplication&, int);
        void autoMove(tileMap&, std::vector <int>&);
        void getRandomVelocity();  //will randomly set one of the velocity vars to be true and rest others to be false
        void killAllVelocity();    //will set all the boolean velocity vars to false
        void setVelocityFactor(int);

};

#endif //ENEMY_H