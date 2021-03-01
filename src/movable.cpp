#include "movable.h"
#include <stdlib.h>
#include <iostream>
#include "myApplication.h"

movable::movable(){}

movable::movable(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app, 
                 bool random_spawn, int spawn_index){
    if (!random_spawn){
        int spawn_index = getRandomSpawn(level);
    }                 
    position_ = getPositionFromIndex(spawn_index, tile_map);

    sprite_.setTexture(app.getTexture(texture_name));
    sprite_.setScale(0.99 * (tile_map.getTileSize().x / sprite_.getGlobalBounds().width), 
                     0.99 * (tile_map.getTileSize().y / sprite_.getGlobalBounds().height));
    sprite_.setPosition(position_);

    right_velocity_ = false;
    left_velocity_ = false;
    up_velocity_ = false;
    down_velocity_ = false;
    is_active_ = false;
}

int movable::getRandomSpawn(std::vector <int>& level){
    std::vector <int> open_points;
    for (int i = 0; i < (int)level.size(); i++){
        if (level[i] != 1){
            open_points.push_back(i);
        }
    }
    int spawn_index = rand() % open_points.size();
    return open_points[spawn_index];
}

sf::Vector2f movable::getPositionFromIndex(int spawn_index, tileMap& tile_map){
    double h_offset = tile_map.getHOffset();
    double w_offset = tile_map.getWOffset();

    int row = tile_map.getRow(spawn_index);
    int col = tile_map.getCol(spawn_index, row);

    return sf::Vector2f((w_offset / 2 + col * tile_map.getTileSize().x), (h_offset / 2 + row * tile_map.getTileSize().y));
}

sf::Sprite& movable::getSprite(){
    return sprite_;
}

int movable::getIndexFromPosition(tileMap& tile_map){
    int row = (int)((position_.y - tile_map.getHOffset() / 2) / tile_map.getTileSize().y);
    int col = (int)((position_.x - tile_map.getWOffset() / 2) / tile_map.getTileSize().x);
    return col + row * tile_map.getNumTiles().x;
}

void movable::move(tileMap& tile_map, std::vector <int>& level){
    int curr_index = this->getIndexFromPosition(tile_map);
    //if (curr_index > 500 || curr_index < 0){std::cout << "error" << std::endl;}

    if (right_velocity_){
        if (level[curr_index + 1] != 1){
            position_ = sf::Vector2f(position_.x + tile_map.getTileSize().x, position_.y);
        }
    }
    else if (left_velocity_){
        if (level[curr_index - 1] != 1){
            position_ = sf::Vector2f(position_.x - tile_map.getTileSize().x, position_.y);
        }
    }
    else if (up_velocity_){
        if (level[curr_index - tile_map.getNumTiles().x] != 1){
            position_ = sf::Vector2f(position_.x, position_.y - tile_map.getTileSize().y);
        }
    }
    else if (down_velocity_){
        if (level[curr_index + tile_map.getNumTiles().x] != 1){
            position_ = sf::Vector2f(position_.x, position_.y + tile_map.getTileSize().y);
        }
    }

    sprite_.setPosition(position_);
}

void movable::setVelocity(const std::string& direction){
    is_active_ = true;
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
    is_active_ = false;
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

bool movable::getActiveStatus(){
    return is_active_;
}