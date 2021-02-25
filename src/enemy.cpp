#include "enemy.h"
#include <stdlib.h>

enemy::enemy(){}

enemy::enemy(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app, int factor, bool random_spawn, int spawn_index) : movable(level, tile_map, texture_name, app, random_spawn, spawn_index){
    velocity_factor_ = factor;
    setSource(spawn_index);
}

enemy::enemy(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app, bool random_spawn, int spawn_index) : movable(level, tile_map, texture_name, app, random_spawn, spawn_index){
    setSource(spawn_index);
}

void enemy::setSource(int index){
    source_ = index;
}

void enemy::setDestination(int index, bool random, std::vector <int>& level){
    if (random){
        destination_ = getRandomSpawn(level);
    }
    else {
        destination_ = index;
    }
}

void enemy::getRandomVelocity(){
    this->killAllVelocity();
    int index =  rand() % 4;
    if (index == 0){
        up_velocity_ = true;
    }
    else if (index == 1){
        down_velocity_ = true;
    }
    else if (index == 2){
        left_velocity_ = true;
    }
    else if (index == 3){
        right_velocity_ = true;
    }
}

void enemy::getVelocityFromIndex(int source, int destination){
    this->killAllVelocity();
    int diff = destination - source;
    if (diff == 1){
        right_velocity_ = true;
    }
    else if (diff == -1){
        left_velocity_ = true;
    }
    else if (diff > 1){
        down_velocity_ = true;
    }
    else {
        up_velocity_ = true;
    }
}

void enemy::autoMove(tileMap& tile_map, std::vector <int>& level, bool random_move){
    if (random_move){
        this->getRandomVelocity();
        for (int i = 1; i <= velocity_factor_; i++){
            this->move(tile_map, level);    
        }
    }
    else {

    }
}

void enemy::killAllVelocity(){
    right_velocity_ = false;
    left_velocity_ = false;
    up_velocity_ = false;
    down_velocity_ = false;
}

void enemy::setVelocityFactor(int factor){
    velocity_factor_ = factor;
}