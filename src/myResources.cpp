#include "myResources.h"
#include <iostream>
#include <fstream>

void myResources::loadFont(sf::Font& font_name, const std::string& file_path){
    if (!font_name.loadFromFile(file_path)){
        std::cout << "Font loading failed from " << file_path << std::endl;
    }
}

void myResources::loadTexture(sf::Texture& texture_name, const std::string& file_path){
    if (!texture_name.loadFromFile(file_path)){
            std::cout << "Texture loading failed from " << file_path << std::endl;
    }
    texture_name.setSmooth(true);
}

void myResources::loadAudio(sf::SoundBuffer& buffer_name, const std::string& file_path){
    if(!buffer_name.loadFromFile(file_path)){
        std::cout << "Audio loading failed from " << file_path << std::endl;
    }
}

void myResources::loadLevel(std::vector <int>& level_name, const std::string& f_name){
    std::ifstream fin (f_name);
    int element;
    while (fin >> element){
        level_name.push_back(element);
    }
}

void myResources::loadAllLevels(){
    this->loadLevel(level_1_, "..//assets//maps//level_1.txt");
    this->loadLevel(level_2_, "..//assets//maps//level_2.txt");
    this->loadLevel(level_3_, "..//assets//maps//level_3.txt");
    this->loadLevel(level_4_, "..//assets//maps//level_4.txt");
    this->loadLevel(level_5_, "..//assets//maps//level_5.txt");
}

void myResources::loadAllFonts(){
    this->loadFont(pac_font_, "../assets/fonts/PAC-FONT.TTF");
    this->loadFont(regular_font_, "../assets/fonts/joystix.ttf");
}

void myResources::loadAllTextures(){
    this->loadTexture(welcome_texture_, "../assets/sprites/screens/welcome.jpg");
    this->loadTexture(end_texture_, "../assets/sprites/screens/end.jpg");
    this->loadTexture(pacman_right_1_, "../assets/sprites/pacman-right/1.png");
    this->loadTexture(pacman_up_1_, "../assets/sprites/pacman-up/1.png");
    this->loadTexture(pacman_down_1_, "../assets/sprites/pacman-down/1.png");
    this->loadTexture(pacman_left_1_, "../assets/sprites/pacman-left/1.png");
    this->loadTexture(ghost_blinky_, "../assets/sprites/ghosts/blinky.png");
    this->loadTexture(ghost_blue_ghost_, "../assets/sprites/ghosts/blue_ghost.png");
    this->loadTexture(ghost_clyde_, "../assets/sprites/ghosts/clyde.png");
    this->loadTexture(ghost_inky_, "../assets/sprites/ghosts/inky.png");
    this->loadTexture(ghost_pinky_, "../assets/sprites/ghosts/pinky.png");
    this->loadTexture(food_dot_, "../assets/sprites/extra/dot.png");
    this->loadTexture(game_, "../assets/sprites/extra/game.png");
}

void myResources::loadAllAudio(){
    this->loadAudio(welcome_sound_buff_, "../assets/sounds/pacman_beginning.wav");
    this->loadAudio(eat_sound_buff_, "../assets/sounds/pacman_eatfruit.wav");
    this->loadAudio(die_sound_buff_, "../assets/sounds/pacman_death.wav");
    this->loadAudio(interval_sound_buff_, "../assets/sounds/pacman_intermission.wav");
}

void myResources::loadAllResources(){
    this->loadAllFonts();
    this->loadAllTextures();
    this->loadAllAudio();
    this->loadAllLevels();
}

const std::vector <int>& myResources::getLevel(int level) const{
    if (level == 1)         {return level_1_;}
    else if (level == 2)    {return level_2_;}
    else if (level == 3)    {return level_3_;}
    else if (level == 4)    {return level_4_;}
    else if (level == 5)    {return level_5_;}
}

const sf::Font& myResources::getFont(const std::string& font_name) const{
    if (font_name == "pac_font")            {return pac_font_;}
    else if (font_name == "regular_font")   {return regular_font_;}
}

const sf::Texture& myResources::getTexture(const std::string& texture_name) const{
    if (texture_name == "welcome_texture")      {return welcome_texture_;}
    else if (texture_name == "end_texture")     {return end_texture_;}
    else if (texture_name == "pacman_right_1")  {return pacman_right_1_;}
    else if (texture_name == "pacman_up_1")     {return pacman_up_1_;}
    else if (texture_name == "pacman_left_1")   {return pacman_left_1_;}
    else if (texture_name == "pacman_down_1")   {return pacman_down_1_;}
    else if (texture_name == "ghost_blinky")    {return ghost_blinky_;}
    else if (texture_name == "ghost_blue_ghost"){return ghost_blue_ghost_;}
    else if (texture_name == "ghost_clyde")     {return ghost_clyde_;}
    else if (texture_name == "ghost_inky")      {return ghost_inky_;}
    else if (texture_name == "ghost_pinky")     {return ghost_pinky_;}
    else if (texture_name == "food_dot")        {return food_dot_;}
    else if (texture_name == "game")            {return game_;}
}

const sf::SoundBuffer& myResources::getAudio(const std::string& audio_name) const{
    if (audio_name == "welcome_sound_buff")         {return welcome_sound_buff_;}
    else if (audio_name == "eat_sound_buff")        {return eat_sound_buff_;}
    else if (audio_name == "die_sound_buff")        {return die_sound_buff_;}
    else if (audio_name == "interval_sound_buff")   {return interval_sound_buff_;}
}