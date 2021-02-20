#include "movable.h"
#include <unordered_set>
#include <stdlib.h>
#include <iostream>

movable::movable(myApplication& app, const std::string& texture_name){
    std::vector <int> level = app.getLevel();
    std::unordered_set <int> open_points;
    for (int i = 0; i < (int)level.size(); i++){
        if (level[i] != 1){
            open_points.insert(i);
        }
    }
    int spawn_index = rand() % open_points.size();
    tileMap& tile_map = app.getMap("level 1");
    const double h_offset = tile_map.getHOffset();
    const double w_offset = tile_map.getWOffset();

    int row = spawn_index / tile_map.getNumTiles().x;
    int col = spawn_index - row * tile_map.getNumTiles().x;

    position_ = sf::Vector2f((w_offset / 2 + col * tile_map.getTileSize().x), (h_offset / 2 + row * tile_map.getTileSize().y));
    sprite_.setTexture(app.getTexture(texture_name));
    sprite_.setScale(0.99 * (tile_map.getTileSize().x / sprite_.getGlobalBounds().width), 
                     0.99 * (tile_map.getTileSize().y / sprite_.getGlobalBounds().height));
    sprite_.setPosition(position_);
}

sf::Sprite& movable::getSprite(){
    return sprite_;
}