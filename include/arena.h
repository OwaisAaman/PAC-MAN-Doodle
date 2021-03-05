#ifndef ARENA_H
#define ARENA_H

#include "pacMan.h"
#include "enemy.h"
#include "tileMap.h"

class myApplication;

class arena{
    private:
        tileMap map_;
        std::vector <int> arena_map_array_;
        pacMan pac_man_;
        enemy enemy_blinky_;
        enemy enemy_clyde_;
        enemy enemy_inky_;
        enemy enemy_pinky_;
        int arena_food_count_;
        bool refresh_map_;
        bool level_clear_;
    public:
        arena();
        void setArenaMapArray(myApplication&);
        void arenaInit(myApplication&);
        void loadPacMan(myApplication&);
        void loadEnemies(myApplication&);
        void loadAllMovables(myApplication&);
        void loadArenaMap(myApplication&);
        void updateFoodCount();
        void updateFoodCount(int);
        void updateMap(myApplication&);
        void refreshMovables(sf::Vector2f&);
        void checkMap(myApplication&);
        void moveAll();
        void drawAll(myApplication&);
        void setRefreshMap(bool);
        void updateOffsets(myApplication&);
        void setVelocity(myApplication&, const std::string&);
        void killVelocity(const std::string&);
        enemy& getEnemy(const std::string&);
        pacMan& getPacMan();
        std::vector <int>& getMapArray();
        tileMap& getMap();
        int getFoodCount();
        bool getLevelClearStatus();
};

#endif //ARENA_H