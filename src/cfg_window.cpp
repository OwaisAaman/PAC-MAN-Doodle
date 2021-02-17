#include "functions.h"

void cfg_window(sf::RenderWindow& window, const int& width, const int& height) {
    sf::VideoMode videomode;
    videomode.width = 1080;
    videomode.height = 720;
    window.create(videomode, "PAC-MAN");
    window.setFramerateLimit(60); 
}