#include <iostream>
#include <vector>
#include "headerText.h"
#include "myScreen.h"
#include <SFML/Audio.hpp>
#include "myApplication.h"
#include "arena.h"

int main(){

    myApplication app;
    app.appInit(1200, 900);
    app.setCurrentScreenType("game");
    arena my_arena;
    my_arena.arenaInit(app, "level 1");
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
        app.getWindow().clear();
        my_arena.moveAll();
        my_arena.checkMap();
        my_arena.updateMap(app);
        app.updateView();
        app.getCurrentScreen().updateScreen(app);
        app.drawScreen();
        //my_arena.drawAll(app);
        //std::cout << my_arena.getPacMan().getScore() << std::endl;
        app.getWindow().display();
    }
    return 0;
}