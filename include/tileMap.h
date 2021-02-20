#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include "myApplication.h"

//class myApplication;

class tileMap{
    private:
        sf::VertexArray vertices_;
        sf::Texture tile_texture_;
        std::string level_name_;
        double h_offset_;  //horizontal offset for rendering the tilemap on the window
        double w_offset_;   //vertical offset for rendering the tilemap on the window

    public:
        tileMap();
        void loadMap(const std::string&, sf::Vector2u, const int, const int, myApplication&);
        void loadWireFrame(sf::Vector2u, const int, const int, myApplication&);
        void updateHOffset();
        void updateWOffset();
        sf::VertexArray& getTileMap();
};

#endif //TILE_MAP_H