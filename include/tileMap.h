#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <string>
//#include "myApplication.h"

class myApplication;

class tileMap : public sf::Drawable, sf::Transformable {
    private:
        sf::VertexArray vertices_;
        sf::Texture tile_texture_;
        std::string level_name_;
        sf::Vector2u tile_size_;
        sf::Vector2u num_tiles_;
        double h_offset_;  //horizontal offset for rendering the tilemap on the window
        double w_offset_;  //vertical offset for rendering the tilemap on the window
        std::vector <int> level_;
    public:
        tileMap();
        void loadMap(const std::string&, sf::Vector2u, const int, const int, myApplication&);
        void loadWireFrame(sf::Vector2u, const int, const int, myApplication&);
        void updateHOffset();
        void updateWOffset();
        sf::VertexArray& getVertexMap();
        double getHOffset();
        double getWOffset();
        sf::Vector2u getTileSize();
        sf::Vector2u getNumTiles();
        void setLevel(std::vector <int>&);
        std::vector <int>& getLevel();
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
        //virtual void draw(sf::RenderTarget&) const;
};

#endif //TILE_MAP_H