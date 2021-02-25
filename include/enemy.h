#ifndef ENEMY_H
#define ENEMY_H

#include "myApplication.h"
#include "movable.h"

class enemy : public movable{
    private:
        int velocity_factor_;
        int source_;
        int destination_;
        std::vector <int> path_;
    public:
        enemy();
        enemy(std::vector <int>&, tileMap&, const std::string&, myApplication&, bool, int);
        enemy(std::vector <int>&, tileMap&, const std::string&, myApplication&, int, bool, int);
        void autoMove(tileMap&, std::vector <int>&, bool);
        void setSource(int);
        void setDestination(int, bool, std::vector <int>&);
        void getRandomVelocity();  //will randomly set one of the velocity vars to be true and rest others to be false
        void killAllVelocity();    //will set all the boolean velocity vars to false
        void setVelocityFactor(int);
        void getVelocityFromIndex(int, int);

};

#endif //ENEMY_H