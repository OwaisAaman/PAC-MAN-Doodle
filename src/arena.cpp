#include "arena.h"
#include "enemy.h"
#include "pacMan.h"
#include "movable.h"

arena::arena(){
    map_ = tileMap();
}

void arena::setArenaMapArray(myApplication& app, const std::string& level_name){
    arena_map_array_ = app.getLevel(level_name);
}

void arena::arenaInit(myApplication& app, const std::string& level_name){
    setArenaMapArray(app, level_name);
    map_.loadMap(arena_map_array_, sf::Vector2u(32, 32) , 20, 25, app);
    loadAllMovables(app);
}

void arena::loadPacMan(myApplication& app){
    pac_man_ = pacMan(arena_map_array_, map_, "pacman_right_1", app);
}

void arena::loadEnemies(myApplication& app){
    enemy_blinky_ = enemy(arena_map_array_, map_, "ghost_blinky", app, 1);
    enemy_blue_ = enemy(arena_map_array_, map_, "ghost_blue_ghost", app, 1);
    enemy_clyde_ = enemy(arena_map_array_, map_, "ghost_clyde", app, 1);
    enemy_inky_ = enemy(arena_map_array_, map_, "ghost_inky", app, 1);
    enemy_pinky_ = enemy(arena_map_array_, map_, "ghost_pinky", app, 1);
}

void arena::loadAllMovables(myApplication& app){
    loadPacMan(app);
    loadEnemies(app);
}

void arena::moveAll(){
    pac_man_.move(map_, arena_map_array_);
    enemy_blinky_.autoMove(map_, arena_map_array_);
    enemy_blue_.autoMove(map_, arena_map_array_);
    enemy_clyde_.autoMove(map_, arena_map_array_);
    enemy_inky_.autoMove(map_, arena_map_array_);
    enemy_pinky_.autoMove(map_, arena_map_array_);
}

void arena::drawAll(myApplication& app){
    app.getWindow().draw(map_);
    app.getWindow().draw(pac_man_.getSprite());
    app.getWindow().draw(enemy_blinky_.getSprite());
    app.getWindow().draw(enemy_blue_.getSprite());
    app.getWindow().draw(enemy_clyde_.getSprite());
    app.getWindow().draw(enemy_inky_.getSprite());
    app.getWindow().draw(enemy_pinky_.getSprite());
}

pacMan& arena::getPacMan(){
    return pac_man_;
}

enemy& arena::getEnemy(const std::string& name){
    if (name == "ghost_blinky"){
        return enemy_blinky_;
    }
    else if (name == "ghost_blue_ghost"){
        return enemy_blue_;
    }
    else if (name == "ghost_clyde"){
        return enemy_clyde_;
    }
    else if (name == "ghost_inky"){
        return enemy_inky_;
    }
    else if (name == "ghost_pinky"){
        return enemy_pinky_;
    }
}

std::vector <int>& arena::getMapArray(){
    return arena_map_array_;
}