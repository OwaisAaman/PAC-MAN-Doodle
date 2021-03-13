#include "enemy.h"
#include <stdlib.h>  //for random velocity
#include "aStar.h"
#include "myApplication.h"

enemy::enemy(){
    velocity_factor_ = 1;
    counter_ = 0;
    is_frozen_ = false;
    reached_spawn_ = false;
}

enemy::enemy(const std::vector <int>& level, const tileMap& tile_map, const std::string& texture_name, const myApplication& app, const bool random_spawn, const int spawn_index, const int wait_time) : movable(level, tile_map, texture_name, app, random_spawn, spawn_index){
    *this = enemy();
    this->setSource(spawn_index);
    this->setDestination(spawn_index - tile_map.getNumTiles().x, false, level);
    this->initFirstPath(wait_time);
}

enemy::enemy(const std::vector <int>& level, const tileMap& tile_map, const std::string& texture_name, const myApplication& app, const int factor, const bool random_spawn, const int spawn_index, const int wait_time) : movable(level, tile_map, texture_name, app, random_spawn, spawn_index){
    *this = enemy(level, tile_map, texture_name, app, random_spawn, spawn_index, wait_time);
    velocity_factor_ = factor;
}

void enemy::initFirstPath(const int wait_time){
    for (int i = 0; i < wait_time; i++){
        if (i % 2 == 0) {path_.push_back(destination_);}
        else            {path_.push_back(source_);}
    }
}

void enemy::setSource(const int index){
    source_ = index;
}

void enemy::setDestination(const int index, const bool random, const std::vector <int>& level){
    if (random) {destination_ = getRandomSpawn(level);}
    else        {destination_ = index;}
}

void enemy::getRandomVelocity(){
    this->killAllVelocity();
    is_active_ = true;
    int index =  rand() % 4;

    if (index == 0)         {up_velocity_ = true;}
    else if (index == 1)    {down_velocity_ = true;}
    else if (index == 2)    {left_velocity_ = true;}
    else if (index == 3)    {right_velocity_ = true;}
}

void enemy::getVelocityFromIndex(int source, int destination){
    this->killAllVelocity();
    is_active_ = true;
    int diff = destination - source;

    if (diff == 1)          {right_velocity_ = true;}
    else if (diff == -1)    {left_velocity_ = true;}
    else if (diff > 1)      {down_velocity_ = true;}
    else                    {up_velocity_ = true;}
}

void enemy::callAstar(const tileMap& tile_map, const std::vector <int>& level, const int source, const int destination, const bool random_destination){
    this->setDestination(destination, random_destination, level);
    aStar::pathFind path;
    std::vector <int> new_path = path.getPath(source, destination_, tile_map, level);
    new_path.pop_back();
    std::reverse(new_path.begin(), new_path.end());
    path_.insert(std::end(path_), std::begin(new_path), std::end(new_path));
}

void enemy::traversePath(const tileMap& tile_map, const std::vector <int>& level){
    this->getVelocityFromIndex(source_, path_.front());
    this->move(tile_map, level);
    this->setSource(path_.front());
    path_.erase(path_.begin());
    
    if (path_.size() < 20 && is_alive_){
        this->callAstar(tile_map, level, path_.back(), 0, true);
    }
}

void enemy::autoMove(const tileMap& tile_map, const std::vector <int>& level, const bool random_move){
    //autonomous movement of ghosts, handling random as well as directed movements
    if (random_move){
        this->getRandomVelocity();
        for (int i = 1; i <= velocity_factor_; i++){
            this->move(tile_map, level);    
        }
    }
    else {
        if (velocity_factor_ < 1){
            ++counter_;
            if (counter_ > 1){
                this->traversePath(tile_map, level);
                counter_ = 0;
            }
        }
        for (int i = 1; i <= velocity_factor_; i++){
            if (path_.empty()){
                reached_spawn_ = true;
                break;
            }
            this->traversePath(tile_map, level);
        }
    }
}

void enemy::freeze(const myApplication& app){
    //ghosts are vulnerable when pacman eats a big pill
    if (!is_frozen_ && is_alive_){
        is_frozen_ = true;
        this->sprite_.setTexture(app.getTexture("ghost_blue_ghost"));
        this->setVelocityFactor(0);
    }
}

void enemy::unfreeze(const myApplication& app, const std::string& texture_name){
    if (is_frozen_){
        is_frozen_ = false;
        this->sprite_.setTexture(app.getTexture(texture_name));
        this->setVelocityFactor(1);
    }
}

void enemy::kill(const tileMap& map, const std::vector <int>& level, const int destination){
    if (is_alive_){
        is_alive_ = false;
        is_frozen_ = false;
        int index = this->getIndexFromPosition(map);
        this->setVelocityFactor(2);
        this->callAstar(map, level, index, destination, false);
    }
}

void enemy::setVelocityFactor(int factor){
    velocity_factor_ = factor;
}

const bool enemy::getFreezeStatus(){
    return is_frozen_;
}

const bool enemy::getReachedSpawnStatus(){
    return reached_spawn_;
}