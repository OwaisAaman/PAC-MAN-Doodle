#include <iostream>
#include <vector>
#include "header_text.h"
#include "functions.h"

int main(){

    sf::RenderWindow window;
    cfg_window(window, 1080, 720);
    
    sf::Font pac_font;
    if (!pac_font.loadFromFile("../assets/fonts/PAC-FONT.TTF")){
        std::cout << "Font loading failed" << std::endl;
    }

    sf::Font basic_font;
    if (!basic_font.loadFromFile("../assets/fonts/joystix.ttf")){
        std::cout << "Font loading failed" << std::endl;
    }

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        draw_text(pac_font, basic_font, window);
        window.display();

    }


    return 0;
}