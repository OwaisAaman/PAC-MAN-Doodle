#include <iostream>
#include <vector>
#include "headerText.h"
#include "myScreen.h"
#include <SFML/Audio.hpp>
#include "myApplication.h"
#include "tileMap.h"
#include "pacMan.h"
#include "arena.h"


int main(){

    myApplication app;
    tileMap my_wire_frame, my_map;
    app.appInit(1200, 900);
    app.setCurrentScreenType("end");
    my_wire_frame.loadWireFrame(sf::Vector2u(28, 28) , 25, 29, app);
    my_map.loadMap("level 1", sf::Vector2u(28, 28) , 25, 29, app);
    //pacMan paccy(app);
    //movable paccy(app, "pacman_right_1");
    arena my_arena;
    my_arena.loadAll(app);
    pacMan& paccy = my_arena.getPacMan();


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
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
                paccy.setVelocity("Up");
                paccy.setTexture(app, "pacman_up_1");
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
                paccy.setVelocity("Down");
                paccy.setTexture(app, "pacman_down_1");
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right){
                paccy.setVelocity("Right");
                paccy.setTexture(app, "pacman_right_1");
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left){
                paccy.setVelocity("Left");
                paccy.setTexture(app, "pacman_left_1");
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up){
                paccy.killVelocity("Up");
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down){
                paccy.killVelocity("Down");
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left){
                paccy.killVelocity("Left");
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right){
                paccy.killVelocity("Right");
            }
        }
        //paccy.move();
        my_arena.moveAll();
        app.getWindow().clear();
        app.updateView();
        app.getCurrentScreen().updateScreen(app);
        //app.drawScreen();
        app.getWindow().draw(my_wire_frame.getVertexMap());
        app.getWindow().draw(my_map.getVertexMap());
        my_arena.drawAll(app);
        //app.getWindow().draw(paccy.getSprite());
        app.getWindow().display();
    }
    return 0;
}