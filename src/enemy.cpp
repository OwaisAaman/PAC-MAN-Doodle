#include "enemy.h"
#include <stdlib.h>
#include "aStar.h"
#include <iostream>
#include "myApplication.h"
#include <thread> 

enemy::enemy(){}

enemy::enemy(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app, int factor, bool random_spawn, int spawn_index) : movable(level, tile_map, texture_name, app, random_spawn, spawn_index){
    velocity_factor_ = factor;
    setSource(spawn_index);
    setDestination(spawn_index - tile_map.getNumTiles().x, false, level);
    initFirstPath();
}


enemy::enemy(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app, bool random_spawn, int spawn_index) : movable(level, tile_map, texture_name, app, random_spawn, spawn_index){
    setSource(spawn_index);
    setDestination(spawn_index - tile_map.getNumTiles().x, false, level);
    initFirstPath();
}

void enemy::initFirstPath(){
    for (int i = 0; i < 9; i++){
        if (i % 2 == 0){
            path_.push_back(destination_);
        }
        else {
            path_.push_back(source_);
        }
    }
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
    is_active_ = true;
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
    is_active_ = true;
}

void enemy::callAstar(tileMap& tile_map, std::vector <int>& level){
    //std::cout << "astar called" << std::endl;
    setDestination(0, true, level);
    aStar::pathFind path;
    std::vector <int> new_path;
    new_path = path.getPath(path_.back(), destination_, tile_map, level);
    new_path.pop_back();
    std::reverse(new_path.begin(), new_path.end());
    path_.insert(std::end(path_), std::begin(new_path), std::end(new_path));
}

void enemy::autoMove(tileMap& tile_map, std::vector <int>& level, bool random_move){
    if (random_move){
        this->getRandomVelocity();
        for (int i = 1; i <= velocity_factor_; i++){
            this->move(tile_map, level);    
        }
    }
    else {
        //std::cout << "the path is " << std::endl;
        //log(path_);
        for (int i = 1; i <= velocity_factor_; i++){
            int temp_dest = path_.front();
            path_.erase(path_.begin());
            getVelocityFromIndex(source_, temp_dest);
            move(tile_map, level);
            setSource(temp_dest);
            
            if (path_.size() < 20){
                //std::thread new_thread_(&enemy::callAstar, tile_map, level);
                callAstar(tile_map, level);
            }
        }
    }
}

void enemy::setVelocityFactor(int factor){
    velocity_factor_ = factor;
}

void enemy::log(const std::vector <int>& level){
    for (int i = 0; i < (int)level.size(); i++){
        std::cout << level[i] << " ";
    }
    std::cout << std::endl;
}