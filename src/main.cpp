#include <iostream>
#include <SFML/Audio.hpp>
#include "myApplication.h"

int main(){
    sf::SoundBuffer intro_buffer;
    if(!intro_buffer.loadFromFile("../assets/sounds/pacman_beginning.wav")){
        std::cout << "intro sound buffer not loaded" << std::endl;
    }

    sf::Sound intro_sound;
    intro_sound.setBuffer(intro_buffer);
    intro_sound.play();
    intro_sound.setLoop(true);
    myApplication app;
    app.runApp();

    return 0;
}