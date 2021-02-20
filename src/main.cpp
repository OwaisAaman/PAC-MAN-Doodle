#include <iostream>
#include <vector>
#include "headerText.h"
#include "myScreen.h"
#include <SFML/Audio.hpp>
#include "myApplication.h"
#include "tileMap.h"


int main(){

    myApplication app;
    tileMap my_wire_frame, my_map;
    app.appInit(1200, 900);
    app.setCurrentScreenType("end");
    my_wire_frame.loadWireFrame(sf::Vector2u(28, 28) , 25, 29, app);
    my_map.loadMap("level 1", sf::Vector2u(28, 28) , 25, 29, app);

    sf::SoundBuffer intro_buffer;
    if(!intro_buffer.loadFromFile("../assets/sounds/pacman_beginning.wav")){
        std::cout << "intro sound buffer not loaded" << std::endl;
    }

    sf::Sound intro_sound;
    intro_sound.setBuffer(intro_buffer);
    intro_sound.play();
    intro_sound.setLoop(true);
    
    while (app.getWindow().isOpen()){
        sf::Event event;
        while (app.getWindow().pollEvent(event)){
            if (event.type == sf::Event::Closed){
                app.getWindow().close();
                intro_sound.stop();
            }
        }
        app.getWindow().clear();
        app.updateView();
        app.getCurrentScreen().updateScreen(app);
        //app.drawScreen();
        app.getWindow().draw(my_wire_frame.getTileMap());
        app.getWindow().draw(my_map.getTileMap());
        app.getWindow().display();
    }
    return 0;
}