#include "movable.h"
#include <stdlib.h>
#include <iostream>

movable::movable(){}

movable::movable(myApplication& app, const std::string& texture_name, const std::string& level_name){
    std::vector <int> level = app.getLevel();
    std::vector <int> open_points;
    for (int i = 0; i < (int)level.size(); i++){
        if (level[i] != 1){
            open_points.push_back(i);
        }
    }
    int spawn_index = rand() % open_points.size();
    spawn_index = open_points[spawn_index];
    tileMap& tile_map = app.getMap("level 1");
    const double h_offset = tile_map.getHOffset();
    const double w_offset = tile_map.getWOffset();

    int row = spawn_index / tile_map.getNumTiles().x;
    int col = spawn_index - row * tile_map.getNumTiles().x;

    //std::cout << h_offset << " " << w_offset << std::endl;

    position_ = sf::Vector2f((w_offset / 2 + col * tile_map.getTileSize().x), (h_offset / 2 + row * tile_map.getTileSize().y));
    sprite_.setTexture(app.getTexture(texture_name));
    sprite_.setScale(0.99 * (tile_map.getTileSize().x / sprite_.getGlobalBounds().width), 
                     0.99 * (tile_map.getTileSize().y / sprite_.getGlobalBounds().height));
    sprite_.setPosition(position_);

    //std::cout << level[0] << " " << level[1] << std::endl;
    //std::cout << spawn_index << std::endl;
    //std::cout << position_.x << " " << position_.y << std::endl;

    this->setMap(app, level_name);
    right_velocity_ = false;
    left_velocity_ = false;
    up_velocity_ = false;
    down_velocity_ = false;
}

sf::Sprite& movable::getSprite(){
    return sprite_;
}

void movable::setMap(myApplication& app, const std::string& level_name){
    this->map_ = app.getMap(level_name);
}

int movable::getIndexFromPosition(){
    int row = (int)((position_.y - map_.getHOffset() / 2) / map_.getTileSize().y);
    int col = (int)((position_.x - map_.getWOffset() / 2) / map_.getTileSize().x);
    return col + row * map_.getNumTiles().x;
}

void movable::move(){
    int curr_index = this->getIndexFromPosition();
    if (curr_index > 500 || curr_index < 0){std::cout << "error" << std::endl;}
    //std::cout << curr_index << std::endl;
    if (right_velocity_){
        if (map_.getLevel()[curr_index + 1] != 1){
            position_ = sf::Vector2f(position_.x + map_.getTileSize().x, position_.y);
        }
    }
    else if (left_velocity_){
        if (map_.getLevel()[curr_index - 1] != 1){
            position_ = sf::Vector2f(position_.x - map_.getTileSize().x, position_.y);
        }
    }
    else if (up_velocity_){
        if (map_.getLevel()[curr_index - map_.getNumTiles().x] != 1){
            position_ = sf::Vector2f(position_.x, position_.y - map_.getTileSize().y);
        }
    }
    else if (down_velocity_){
        if (map_.getLevel()[curr_index + map_.getNumTiles().x] != 1){
            position_ = sf::Vector2f(position_.x, position_.y + map_.getTileSize().y);
        }
    }
    //std::cout << position_.x << " " << position_.y << std::endl;
    sprite_.setPosition(position_);
}

void movable::setVelocity(const std::string& direction){
    if (direction == "Up"){
        up_velocity_ = true;
    }
    else if (direction == "Down"){
        down_velocity_ = true;
    }
    else if (direction == "Right"){
        right_velocity_ = true;
    }
    else if (direction == "Left"){
        left_velocity_ = true;
    }
}

void movable::killVelocity(const std::string& direction){
    if (direction == "Up"){
        up_velocity_ = false;
    }
    else if (direction == "Down"){
        down_velocity_ = false;
    }
    else if (direction == "Right"){
        right_velocity_ = false;
    }
    else if (direction == "Left"){
        left_velocity_ = false;
    }
}

void movable::setTexture(myApplication& app, const std::string& texture_name){
    sprite_.setTexture(app.getTexture(texture_name));
}