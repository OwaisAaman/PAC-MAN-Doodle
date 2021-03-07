#ifndef ENEMY_H
#define ENEMY_H

#include "movable.h"

class myApplication; 

class enemy : public movable{
    private:
        int velocity_factor_;
        int source_;
        int destination_;
        std::vector <int> path_;
        bool is_frozen_;
        int counter_;
        bool reached_spawn_;
    public:
        enemy();
        enemy(std::vector <int>&, tileMap&, const std::string&, myApplication&, bool, int, int);
        enemy(std::vector <int>&, tileMap&, const std::string&, myApplication&, int, bool, int, int);
        void autoMove(tileMap&, std::vector <int>&, bool);
        void setSource(int);
        void setDestination(int, bool, std::vector <int>&);
        void getRandomVelocity();  //will randomly set one of the velocity vars to be true and rest others to be false
        void setVelocityFactor(int);
        void getVelocityFromIndex(int, int);
        void initFirstPath(int);
        void callAstar(tileMap&, std::vector <int>&);
        void log(const std::vector <int>&);
        void freeze(myApplication&);
        void unfreeze(myApplication&, const std::string&);
        void kill(tileMap&, std::vector <int>&, int);
        bool getFreezeStatus();
        bool getReachedSpawnStatus();
};

#endif //ENEMY_H