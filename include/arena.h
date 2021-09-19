#ifndef ARENA_H
#define ARENA_H

#include "pacMan.h"
#include "enemy.h"
#include "tileMap.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class myApplication;

class arena{
    private:
        tileMap             map_;
        std::vector <int>   arena_map_array_;
        sf::VertexArray     pacman_vertices_;
        sf::Texture         pacman_texture_;
        pacMan              pac_man_;
        enemy               enemy_blinky_;
        enemy               enemy_clyde_;
        enemy               enemy_inky_;
        enemy               enemy_pinky_;
        sf::Clock           clock_;
        int                 arena_food_count_;
        int                 pacman_lives_;
        int                 arena_score_;
        bool                refresh_map_;
        bool                level_clear_;
        bool                game_over_;
        bool                freeze_enemies_;
        bool                already_frozen_;
        sf::Sound           pacman_dead_;
        sf::Sound           enemy_dead_;
    public:
        arena();
        void setArenaMapArray(myApplication&);
        void arenaInit(myApplication&);
        void loadPacMan(myApplication&);
        void loadEnemies(myApplication&);
        void loadAllMovables(myApplication&);
        void respawnAllMovables(myApplication&);
        void loadArenaMap(myApplication&);
        void loadPacManVertices();
        void drawPacManVertices(sf::RenderTarget&);
        void updateFoodCount();
        void updateFoodCount(int);
        void updatePacManLives(int);
        void updateMap(myApplication&);
        void refreshMovables(sf::Vector2f&);
        void checkMap(myApplication&);
        void checkCollision(enemy&, int);
        void checkAllCollisions();
        void moveAll();
        void drawAll(myApplication&);
        void setRefreshMap(bool);
        void updateOffsets(myApplication&);
        void setVelocity(myApplication&, const std::string&);
        void killVelocity(const std::string&);
        void freezeEnemies(const int);    //checks on the basis of the food pill wether or not to freeze the enemies. changes the bool value
        void freezeAllEnemies(myApplication&);  //calls the freeze method of each enemy
        void unfreezeAllEnemies(myApplication&);
        enemy& getEnemy(const std::string&);
        pacMan& getPacMan();
        std::vector <int>& getMapArray();
        tileMap& getMap();
        int getFoodCount();
        int getPacManLives();
        bool getLevelClearStatus();
        bool getGameOverStatus();
        void killPacMan();
        void killEnemy(enemy&, int);
        void respawnEnemy(myApplication&, enemy&, const std::string&, int);
        void respawnAllEnemies(myApplication&);
        void updatePacManTiles(myApplication&);
};

#endif //ARENA_H