#include "enemy.h"
#include <stdlib.h>

enemy::enemy(){}

enemy::enemy(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app, int factor) : movable(level, tile_map, texture_name, app){
    velocity_factor_ = factor;
}

enemy::enemy(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app) : movable(level, tile_map, texture_name, app){}

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

void enemy::autoMove(tileMap& tile_map, std::vector <int>& level){
    this->getRandomVelocity();
    for (int i = 1; i <= velocity_factor_; i++){
        this->move(tile_map, level);    
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