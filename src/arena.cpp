#include "arena.h"
#include <iostream>
#include "myApplication.h"

arena::arena(){
    map_ = tileMap();
    arena_food_count_ = 0;
}

void arena::setArenaMapArray(myApplication& app, const std::string& level_name){
    arena_map_array_ = app.getLevel(level_name);
}

void arena::loadArenaMap(myApplication& app){
    map_.loadMap(arena_map_array_, sf::Vector2u(32, 32) , 21, 25, app);
}

void arena::arenaInit(myApplication& app, const std::string& level_name){
    setArenaMapArray(app, level_name);
    loadArenaMap(app);
    loadAllMovables(app);
    updateFoodCount();
    refresh_map_ = false;
}

void arena::loadPacMan(myApplication& app){
    pac_man_ = pacMan(arena_map_array_, map_, "pacman_right_1", app, false, 325);
}

void arena::loadEnemies(myApplication& app){
    enemy_blinky_ = enemy(arena_map_array_, map_, "ghost_blinky", app, 1, false, 281);
    enemy_blue_ = enemy(arena_map_array_, map_, "ghost_blue_ghost", app, 1, false, 282);
    enemy_clyde_ = enemy(arena_map_array_, map_, "ghost_clyde", app, 1, false, 283);
    enemy_inky_ = enemy(arena_map_array_, map_, "ghost_inky", app, 1, false, 284);
    enemy_pinky_ = enemy(arena_map_array_, map_, "ghost_pinky", app, 1, false, 285);
}

void arena::loadAllMovables(myApplication& app){
    loadPacMan(app);
    loadEnemies(app);
}

void arena::updateFoodCount(){
    int fc = 0;
    for (int i = 0; i < (int)arena_map_array_.size(); i++){
        if (arena_map_array_[i] == 0){
            fc++;
        }
    }
    arena_food_count_ = fc;
}

void arena::updateFoodCount(int number){
    arena_food_count_ += number;
}

void arena::updateMap(myApplication& app){
    if (refresh_map_){
        loadArenaMap(app);
        refresh_map_ = false;
    }
}

void arena::refreshMovables(sf::Vector2f& delta){
    pac_man_.getSprite().move(delta);
    enemy_blinky_.getSprite().move(delta);
    enemy_blue_.getSprite().move(delta);
    enemy_clyde_.getSprite().move(delta);
    enemy_inky_.getSprite().move(delta);
    enemy_pinky_.getSprite().move(delta);
}

void arena::setRefreshMap(bool value){
    refresh_map_ = value;
}

void arena::moveAll(){
    pac_man_.move(map_, arena_map_array_);
    enemy_blinky_.autoMove(map_, arena_map_array_, true);
    enemy_blue_.autoMove(map_, arena_map_array_, true);
    enemy_clyde_.autoMove(map_, arena_map_array_, true);
    enemy_inky_.autoMove(map_, arena_map_array_, true);
    enemy_pinky_.autoMove(map_, arena_map_array_, true);
}

void arena::drawAll(myApplication& app){
    checkMap();
    updateMap(app);
    app.getWindow().draw(map_);
    app.getWindow().draw(pac_man_.getSprite());
    app.getWindow().draw(enemy_blinky_.getSprite());
    app.getWindow().draw(enemy_blue_.getSprite());
    app.getWindow().draw(enemy_clyde_.getSprite());
    app.getWindow().draw(enemy_inky_.getSprite());
    app.getWindow().draw(enemy_pinky_.getSprite());
}

void arena::checkMap(){
    int pacman_index = pac_man_.getIndexFromPosition(map_);
    if (arena_map_array_[pacman_index] == 0 && pac_man_.getActiveStatus() == true){
        arena_map_array_[pacman_index] = -1;
        refresh_map_ = true;
        updateFoodCount();
        pac_man_.updateScore();
    }
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

int arena::getFoodCount(){
    return arena_food_count_;
}

tileMap& arena::getMap(){
    return map_;
}

void arena::updateOffsets(myApplication& app){
    map_.updateWOffset(app);
    map_.updateHOffset(app);
}