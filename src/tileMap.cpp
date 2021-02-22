#include "tileMap.h"
#include "myApplication.h"
#include <iostream>

tileMap::tileMap() {
    h_offset_ = 0;
    w_offset_ = 0;
}

void tileMap::loadWireFrame(sf::Vector2u tile_size, const int x_tiles, const int y_tiles, myApplication& app){
    level_name_ = "wire-frame";
    tile_size_ = tile_size;
    h_offset_ = app.getDefaultWindowHeight() - y_tiles * tile_size.y;
    w_offset_ = app.getDefaultWindowWidth() - x_tiles * tile_size.x;
    //std::cout << "wire" << y_tiles << " " << x_tiles << std::endl;
    //std::cout << "wire" << h_offset_ << " " << w_offset_ << std::endl;
    num_tiles_ = sf::Vector2u(x_tiles, y_tiles);
    vertices_.setPrimitiveType(sf::Points);
    vertices_.resize(x_tiles * y_tiles);

    for (int i = 0; i < y_tiles; i++){
        for (int j = 0; j < x_tiles; j++){
            vertices_[i * x_tiles + j].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
            vertices_[i * x_tiles + j].color = sf::Color::Yellow;
        }
    }
}

void tileMap::loadMap(const std::string& level_name, sf::Vector2u tile_size, const int x_tiles, const int y_tiles, myApplication& app){
    if (level_name == "wire-frame"){
        loadWireFrame(tile_size, x_tiles, y_tiles, app);
    }
    else {
        level_name_ = level_name;
        h_offset_ = app.getDefaultWindowHeight() - y_tiles * tile_size.y;
        w_offset_ = app.getDefaultWindowWidth() - x_tiles * tile_size.x;
        //std::cout << "map" << h_offset_ << " " << w_offset_ << std::endl;
        vertices_.setPrimitiveType(sf::Quads);
        vertices_.resize(x_tiles * y_tiles * 4);
        tile_size_ = tile_size;
        num_tiles_ = sf::Vector2u(x_tiles, y_tiles);
        tile_texture_ = app.getTexture("game");

        setLevel(app.getLevel());
        int curr_index;
        for (int i = 0; i < y_tiles; i++){
            for (int j = 0; j < x_tiles; j++){
                curr_index = i * x_tiles + j;
                if (level_[curr_index] == 1){
                    sf::Vertex* quad = &vertices_[curr_index * 4];
                    quad[0].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
                    quad[1].position = sf::Vector2f((w_offset_ / 2 + (j + 1) * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
                    quad[2].position = sf::Vector2f((w_offset_ / 2 + (j + 1) * tile_size.x), (h_offset_ / 2 + (i + 1) * tile_size.y));
                    quad[3].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + (i + 1) * tile_size.y));

                    quad[0].color = sf::Color::Red;
                    //quad[1].color = sf::Color::Yellow;
                    //quad[2].color = sf::Color::Red;
                    //quad[3].color = sf::Color::Yellow;

                    quad[0].texCoords = sf::Vector2f(17, 1);
                    quad[1].texCoords = sf::Vector2f(32, 1);
                    quad[2].texCoords = sf::Vector2f(32, 16);
                    quad[3].texCoords = sf::Vector2f(17, 16);

                }
                else if (level_[curr_index] == 0){
                    sf::Vertex* quad = &vertices_[curr_index * 4];
                    quad[0].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
                    quad[1].position = sf::Vector2f((w_offset_ / 2 + (j + 1) * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
                    quad[2].position = sf::Vector2f((w_offset_ / 2 + (j + 1) * tile_size.x), (h_offset_ / 2 + (i + 1) * tile_size.y));
                    quad[3].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + (i + 1) * tile_size.y));

                    quad[0].texCoords = sf::Vector2f(1, 1);
                    quad[1].texCoords = sf::Vector2f(16, 1);
                    quad[2].texCoords = sf::Vector2f(16, 16);
                    quad[3].texCoords = sf::Vector2f(1, 16);

                    

                }
            }
        }
    }

}

void tileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.texture = &tile_texture_;
    target.draw(vertices_, states);
}
/*
void tileMap::draw(sf::RenderTarget& target) const {
    target.draw(vertices_);
}
*/

void tileMap::setLevel(std::vector <int>& level){
    this->level_ = level;
}

sf::VertexArray& tileMap::getVertexMap(){
    return vertices_;
}

double tileMap::getHOffset(){
    //std::cout << h_offset_ << std::endl;
    return h_offset_;
}

double tileMap::getWOffset(){
    return w_offset_;
}
sf::Vector2u tileMap::getTileSize(){
    return tile_size_;
}

sf::Vector2u tileMap::getNumTiles(){
    return num_tiles_;
}

std::vector <int>& tileMap::getLevel(){
    return level_;
}