#ifndef ENEMY_H
#define ENEMY_H

#include "movable.h"

//class for handling ghosts

class myApplication; 

class enemy : public movable{
    private:
        int                 velocity_factor_;
        int                 source_;
        int                 destination_;
        int                 counter_;
        bool                is_frozen_;
        bool                reached_spawn_;
        std::vector <int>   path_;
    public:
        enemy();
        enemy(const std::vector <int>&, const tileMap&, const std::string&, const myApplication&, const bool, const int, const int);
        enemy(const std::vector <int>&, const tileMap&, const std::string&, const myApplication&, const int, const bool, const int, const int);
        void setSource(const int);
        void setDestination(const int, const bool, const std::vector <int>&);
        void getRandomVelocity();  //will randomly set one of the velocity vars to be true and rest others to be false
        void getVelocityFromIndex(const int, const int);
        void callAstar(const tileMap&, const std::vector <int>&, const int, const int, const bool);
        void traversePath(const tileMap&, const std::vector <int>&);
        void autoMove(const tileMap&, const std::vector <int>&, const bool);
        void setVelocityFactor(const int);
        void initFirstPath(const int);
        void freeze(const myApplication&);
        void unfreeze(const myApplication&, const std::string&);
        void kill(const tileMap&, const std::vector <int>&, const int);
        const bool getFreezeStatus();
        const bool getReachedSpawnStatus();
};

#endif //ENEMY_H