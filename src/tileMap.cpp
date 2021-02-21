#include "tileMap.h"
#include "myApplication.h"

tileMap::tileMap(){
    h_offset_ = 0;
    w_offset_ = 0;
}

void tileMap::loadWireFrame(sf::Vector2u tile_size, const int x_tiles, const int y_tiles, myApplication& app){
    level_name_ = "wire-frame";
    tile_size_ = tile_size;
    h_offset_ = app.getDefaultWindowHeight() - y_tiles * tile_size.y;
    w_offset_ = app.getDefaultWindowWidth() - x_tiles * tile_size.x;
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
        vertices_.setPrimitiveType(sf::Quads);
        vertices_.resize(x_tiles * y_tiles * 4);
        tile_size_ = tile_size;
        num_tiles_ = sf::Vector2u(x_tiles, y_tiles);

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

                    quad[1].color = sf::Color::Yellow;
                    quad[1].color = sf::Color::Yellow;
                    quad[2].color = sf::Color::Yellow;
                    quad[3].color = sf::Color::Yellow;
                }
            }
        }
    }

}
\
void tileMap::setLevel(std::vector <int>& level){
    this->level_ = level;
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

std::vector <int>& tileMap::getLevel(){
    return level_;
}