#include "enemy.h"
#include <stdlib.h>

enemy::enemy(){}

enemy::enemy(myApplication& app, const std::string& texture_name, const std::string& level_name, int factor) : movable(app, texture_name, level_name){
    velocity_factor_ = factor;
}

enemy::enemy(myApplication& app, const std::string& texture_name, const std::string& level_name) : movable(app, texture_name, level_name){}

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

void enemy::autoMove(){
    this->getRandomVelocity();
    for (int i = 1; i <= velocity_factor_; i++){
        this->move();    
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