#include "movable.h"
#include <stdlib.h>  //for random numbers
#include <iostream>
#include "myApplication.h"

movable::movable(){}

movable::movable(const std::vector <int>& level, const tileMap& tile_map, const std::string& texture_name, const myApplication& app, 
                 const bool random_spawn, const int spawn_index){
    if (!random_spawn){
        int spawn_index = getRandomSpawn(level);
    }

    position_ = getPositionFromIndex(spawn_index, tile_map);
    sprite_.setTexture(app.getTexture(texture_name));
    sprite_.setScale(0.99 * (tile_map.getTileSize().x / sprite_.getGlobalBounds().width), 
                     0.99 * (tile_map.getTileSize().y / sprite_.getGlobalBounds().height));
    sprite_.setPosition(position_);

    this->killAllVelocity();
    is_alive_ = true;
}

int movable::getRandomSpawn(const std::vector <int>& level){
    //function to return possible open spaces to move
    //keeping this here to allow the modification of logic of an 'open space'

    std::vector <int> open_points;
    for (int i = 0; i < (int)level.size(); i++){
        if (level[i] != 1){
            open_points.push_back(i);
        }
    }
    int spawn_index = rand() % open_points.size();
    return open_points[spawn_index];
}

sf::Vector2f movable::getPositionFromIndex(const int spawn_index, const tileMap& tile_map){
    //method to resturn x and y coords given the position index 
    double h_offset = tile_map.getHOffset();
    double w_offset = tile_map.getWOffset();
    int row = tile_map.getRow(spawn_index);
    int col = tile_map.getCol(spawn_index, row);

    return sf::Vector2f((w_offset / 2 + col * (float)tile_map.getTileSize().x), (h_offset / 2 + row * (float)tile_map.getTileSize().y));
}

int movable::getIndexFromPosition(const tileMap& tile_map){
    int row = (int)((position_.y - tile_map.getHOffset() / 2) / (float)tile_map.getTileSize().y);
    int col = (int)((position_.x - tile_map.getWOffset() / 2) / (float)tile_map.getTileSize().x);
    return col + row * tile_map.getNumTiles().x;
}

void movable::setVelocity(const std::string& direction){
    is_active_ = true;
    if (direction == "Up")          {up_velocity_ = true;}
    else if (direction == "Down")   {down_velocity_ = true;}
    else if (direction == "Right")  {right_velocity_ = true;}
    else if (direction == "Left")   {left_velocity_ = true;}

    //checking if velocity is provided in two directions. If yes, kill all velocity
    if (up_velocity_ + down_velocity_ + right_velocity_ + left_velocity_ > 1){
        killAllVelocity();
    }
}

void movable::move(const tileMap& tile_map, const std::vector <int>& level){
    int curr_index = this->getIndexFromPosition(tile_map);

    if (right_velocity_ && level[curr_index + 1] != 1){
        position_ = sf::Vector2f(position_.x + (float)tile_map.getTileSize().x, position_.y);
    }
    else if (left_velocity_ && level[curr_index - 1] != 1){
        position_ = sf::Vector2f(position_.x - (float)tile_map.getTileSize().x, position_.y);
    }
    else if (up_velocity_ && level[curr_index - tile_map.getNumTiles().x] != 1){
        position_ = sf::Vector2f(position_.x, position_.y - (float)tile_map.getTileSize().y);
    }
    else if (down_velocity_ && level[curr_index + tile_map.getNumTiles().x] != 1){
        position_ = sf::Vector2f(position_.x, position_.y + (float)tile_map.getTileSize().y);
    }

    sprite_.setPosition(position_);
}

void movable::setPosition(const sf::Vector2f new_position){
    position_ = new_position;
    sprite_.setPosition(position_);
}

void movable::killVelocity(const std::string& direction){
    is_active_ = false;

    if (direction == "Up")          {up_velocity_ = false;}
    else if (direction == "Down")   {down_velocity_ = false;}
    else if (direction == "Right")  {right_velocity_ = false;}
    else if (direction == "Left")   {left_velocity_ = false;}
}

void movable::killAllVelocity(){
    is_active_ = false;
    right_velocity_ = false;
    left_velocity_ = false;
    up_velocity_ = false;
    down_velocity_ = false;
}

void movable::setTexture(const myApplication& app, const std::string& texture_name){
    sprite_.setTexture(app.getTexture(texture_name));
}

void movable::updateActiveStatus(){
    if (right_velocity_ + up_velocity_ + left_velocity_ + down_velocity_ > 0){
        is_active_ = true;
    }
    else {
        is_active_ = false;
    }
}

const bool movable::getActiveStatus(){
    return is_active_;
}

const bool movable::getAliveStatus(){
    return is_alive_;
}

sf::Vector2f movable::getPosition(){
    return position_;
}

sf::Sprite& movable::getSprite(){
    return sprite_;
}