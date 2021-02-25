#include "tileMap.h"
#include "myApplication.h"
#include <algorithm>
#include <iostream>

tileMap::tileMap() {
    h_offset_ = 0;
    w_offset_ = 0;
}

void tileMap::updateHOffset(sf::Vector2u tile_size, const int y_tiles, myApplication& app){
    h_offset_ = app.getDefaultWindowHeight() - y_tiles * tile_size.y;   //change from def size to curr size and set the bool of update tile map to be true
}

void tileMap::updateWOffset(sf::Vector2u tile_size, const int x_tiles, myApplication& app){
    w_offset_ = app.getDefaultWindowWidth() - x_tiles * tile_size.x;   //change from def size to curr size and set the bool of update tile map to be true
}

void tileMap::setTileSize(sf::Vector2u tile_size){
    tile_size_ = tile_size;
}

void tileMap::setNumTiles(const int x_tiles, const int y_tiles){
    num_tiles_ = sf::Vector2u(x_tiles, y_tiles);
}

void tileMap::mapInit(sf::Vector2u tile_size, const int x_tiles, const int y_tiles, myApplication& app){
    setTileSize(tile_size);
    updateHOffset(tile_size, y_tiles, app);
    updateWOffset(tile_size, x_tiles, app);
    setNumTiles(x_tiles, y_tiles);
    tile_texture_ = app.getTexture("game");
}

void tileMap::loadWireFrame(sf::Vector2u tile_size, const int x_tiles, const int y_tiles, myApplication& app){
    this->mapInit(tile_size, x_tiles, y_tiles, app);
    vertices_.setPrimitiveType(sf::Points);
    vertices_.resize(x_tiles * y_tiles);

    for (int i = 0; i < y_tiles; i++){
        for (int j = 0; j < x_tiles; j++){
            vertices_[i * x_tiles + j].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
            vertices_[i * x_tiles + j].color = sf::Color::Yellow;
        }
    }
}

void tileMap::resetVertexMap(){
    vertices_.resize(0);
}

void tileMap::loadMap(std::vector <int>& level, sf::Vector2u tile_size, const int x_tiles, const int y_tiles, myApplication& app){
    this->mapInit(tile_size, x_tiles, y_tiles, app);
    resetVertexMap();
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(x_tiles * y_tiles * 4);

    int curr_index;
    for (int i = 0; i < y_tiles; i++){
        for (int j = 0; j < x_tiles; j++){
            curr_index = i * x_tiles + j;
            if (level[curr_index] == 1){
                sf::Vertex* quad = &vertices_[curr_index * 4];
                quad[0].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
                quad[1].position = sf::Vector2f((w_offset_ / 2 + (j + 1) * tile_size.x), (h_offset_ / 2 + i * tile_size.y));
                quad[2].position = sf::Vector2f((w_offset_ / 2 + (j + 1) * tile_size.x), (h_offset_ / 2 + (i + 1) * tile_size.y));
                quad[3].position = sf::Vector2f((w_offset_ / 2 + j * tile_size.x), (h_offset_ / 2 + (i + 1) * tile_size.y));

                //quad[0].texCoords = sf::Vector2f(17, 1);
                //quad[1].texCoords = sf::Vector2f(32, 1);
                //quad[2].texCoords = sf::Vector2f(32, 16);
                //quad[3].texCoords = sf::Vector2f(17, 16);

                quad[0].texCoords = sf::Vector2f(19, 3);
                quad[1].texCoords = sf::Vector2f(30, 3);
                quad[2].texCoords = sf::Vector2f(30, 14);
                quad[3].texCoords = sf::Vector2f(19, 14);

                quad[0].color = sf::Color::Yellow;
                //quad[2].color = sf::Color::Red;

            }
            else if (level[curr_index] == 0){
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

void tileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.texture = &tile_texture_;
    target.draw(vertices_, states);
}

sf::VertexArray& tileMap::getVertexMap(){
    return vertices_;
}

double tileMap::getHOffset(){
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

int tileMap::getRow(int& spawn_index){
    return spawn_index / num_tiles_.x;
}

int tileMap::getCol(int& spawn_index, int& row){
    return spawn_index - row * num_tiles_.x;
}