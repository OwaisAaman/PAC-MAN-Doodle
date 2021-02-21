#ifndef ARENA_H
#define ARENA_H

#include "movable.h"
#include "pacMan.h"
#include "enemy.h"

class arena{
    private:
        pacMan pac_man_;
        enemy enemy_blinky_;
        enemy enemy_blue_;
        enemy enemy_clyde_;
        enemy enemy_inky_;
        enemy enemy_pinky_;
    public:
        arena();
        void loadPacMan(myApplication&);
        void loadEnemies(myApplication&);
        void loadAll(myApplication&);
        void moveAll();
        enemy& getEnemy(const std::string&);
        pacMan& getPacMan();
        void drawAll(myApplication&);
};

#endif //ARENA_H