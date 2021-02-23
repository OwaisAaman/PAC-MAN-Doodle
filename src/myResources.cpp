#include "myResources.h"
#include <iostream>

void myResources::loadFont(sf::Font& font_name, const std::string& file_path){
    if (!font_name.loadFromFile(file_path)){
        std::cout << "Font loading failed from " << file_path << std::endl;
    }
}

void myResources::loadAllFonts(){
    loadFont(pac_font_, "../assets/fonts/PAC-FONT.TTF");
    loadFont(regular_font_, "../assets/fonts/joystix.ttf");
}

void myResources::loadTexture(sf::Texture& texture_name, const std::string& file_path){
    if (!texture_name.loadFromFile(file_path)){
            std::cout << "Texture loading failed from " << file_path << std::endl;
    }
    texture_name.setSmooth(true);
}

void myResources::loadAllTextures(){
    loadTexture(welcome_texture_, "../assets/sprites/screens/welcome.jpg");
    loadTexture(end_texture_, "../assets/sprites/screens/end.jpg");
    loadTexture(pacman_right_1_, "../assets/sprites/pacman-right/1.png");
    loadTexture(pacman_up_1_, "../assets/sprites/pacman-up/1.png");
    loadTexture(pacman_down_1_, "../assets/sprites/pacman-down/1.png");
    loadTexture(pacman_left_1_, "../assets/sprites/pacman-left/1.png");
    loadTexture(ghost_blinky_, "../assets/sprites/ghosts/blinky.png");
    loadTexture(ghost_blue_ghost_, "../assets/sprites/ghosts/blue_ghost.png");
    loadTexture(ghost_clyde_, "../assets/sprites/ghosts/clyde.png");
    loadTexture(ghost_inky_, "../assets/sprites/ghosts/inky.png");
    loadTexture(ghost_pinky_, "../assets/sprites/ghosts/pinky.png");
    loadTexture(food_dot_, "../assets/sprites/extra/dot.png");
    loadTexture(game_, "../assets/sprites/extra/game.png");
}

void myResources::loadAudio(sf::SoundBuffer& buffer_name, const std::string& file_path){
    if(!buffer_name.loadFromFile(file_path)){
        std::cout << "Audio loading failed from " << file_path << std::endl;
    }
}

void myResources::loadAllAudio(){
    loadAudio(welcome_sound_buff_, "../assets/sounds/pacman_beginning.wav");
}

void myResources::loadAllResources(){
    this->loadAllFonts();
    this->loadAllTextures();
    this->loadAllAudio();
    this->loadLevel();
}

void myResources::loadLevel(){
    level_1_ = {1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
                1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1};
}

std::vector <int> myResources::getLevel(const std::string& level_name){
    if (level_name == "level 1"){
        return level_1_;
    }
}

sf::Font& myResources::getFont(const std::string& font_name){
    if (font_name == "pac_font"){
        return pac_font_;
    }
    else if (font_name == "regular_font"){
        return regular_font_;
    }
}

sf::Texture& myResources::getTexture(const std::string& texture_name){
    if (texture_name == "welcome_texture"){
        return welcome_texture_;
    }
    else if (texture_name == "end_texture"){
        return end_texture_;
    }
    else if (texture_name == "pacman_right_1"){
        return pacman_right_1_;
    }
    else if (texture_name == "pacman_up_1"){
        return pacman_up_1_;
    }
    else if (texture_name == "pacman_left_1"){
        return pacman_left_1_;
    }
    else if (texture_name == "pacman_down_1"){
        return pacman_down_1_;
    }
    else if (texture_name == "ghost_blinky"){
        return ghost_blinky_;
    }
    else if (texture_name == "ghost_blue_ghost"){
        return ghost_blue_ghost_;
    }
    else if (texture_name == "ghost_clyde"){
        return ghost_clyde_;
    }
    else if (texture_name == "ghost_inky"){
        return ghost_inky_;
    }
    else if (texture_name == "ghost_pinky"){
        return ghost_pinky_;
    }
    else if (texture_name == "food_dot"){
        return food_dot_;
    }
    else if (texture_name == "game"){
        return game_;
    }

}

sf::SoundBuffer& myResources::getAudio(const std::string& audio_name){
    if (audio_name == "welcome_sound_buff"){
        return welcome_sound_buff_;
    }
}