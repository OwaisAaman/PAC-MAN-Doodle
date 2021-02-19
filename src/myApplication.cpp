#include "myApplication.h"
#include <iostream>

myApplication::myApplication(){}

void myApplication::appInit(){
    loadAllFonts();
    loadAllTextures();
    loadAllAudio();
    configureWindow(1080, 720);
    loadAllScreens();
    updateWindowOrigin();
}

void myApplication::loadFont(sf::Font& font_name, const std::string& file_path){
    if (!font_name.loadFromFile(file_path)){
        std::cout << "Font loading failed from " << file_path << std::endl;
    }
}

void myApplication::loadAllFonts(){
    loadFont(pac_font_, "../assets/fonts/PAC-FONT.TTF");
    loadFont(regular_font_, "../assets/fonts/joystix.ttf");
}

void myApplication::loadTexture(sf::Texture& texture_name, const std::string& file_path){
    if (!texture_name.loadFromFile(file_path)){
            std::cout << "Texture loading failed from " << file_path << std::endl;
    }
}

void myApplication::loadAllTextures(){
    loadTexture(welcome_texture_, "../assets/sprites/screens/welcome.jpg");
    loadTexture(end_texture_, "../assets/sprites/screens/end.jpg");
}

void myApplication::loadAudio(sf::SoundBuffer& buffer_name, const std::string& file_path){
    if(!buffer_name.loadFromFile(file_path)){
        std::cout << "Audio loading failed from " << file_path << std::endl;
    }
}

void myApplication::loadAllAudio(){
    loadAudio(welcome_sound_buff_, "../assets/sounds/pacman_beginning.wav");
}

void myApplication::loadScreen(const std::string& type){
    if (type == "welcome"){
        welcome_screen_.screenInit(this->getWindow(), type);
        welcome_screen_.renderScreen(type, *this);
    }
    else if (type == "end"){
        end_screen_.screenInit(this->getWindow(), type);
        end_screen_.renderScreen(type, *this);
    }
}

void myApplication::loadAllScreens(){
    this->loadScreen("welcome");
    this->loadScreen("end");
}

void myApplication::setCurrentScreenType(const std::string& type){
    current_screen_type_ = type;
}

void myApplication::configureWindow(const int screen_width, const int screen_height){
    videomode_.width = screen_width;
    videomode_.height = screen_height;
    window_.create(videomode_, "PAC-MAN");
    window_.setFramerateLimit(60);
}

void myApplication::updateView(){
    view_.setCenter(window_.getSize().x / 2.f, window_.getSize().y / 2.f);
    view_.setSize(window_.getSize().x, window_.getSize().y);
    window_.setView(view_);
}

void myApplication::updateWindowOrigin(){
    window_origin_ = {window_.getSize().x / 2, window_.getSize().y / 2};
}

void myApplication::drawScreen(){
    if (current_screen_type_ == "welcome"){
        welcome_screen_.drawScreen(*this);
    }
    else if (current_screen_type_ == "end"){
        end_screen_.drawScreen(*this);
    }
}


void myApplication::app_run(){}

sf::Font& myApplication::getFont(const std::string& font_name){
    if (font_name == "pac_font"){
        return pac_font_;
    }
    else if (font_name == "regular_font"){
        return regular_font_;
    }
}

sf::Texture& myApplication::getTexture(const std::string& texture_name){
    if (texture_name == "welcome_texture"){
        return welcome_texture_;
    }
    else if (texture_name == "end_texture"){
        return end_texture_;
    }
}

sf::SoundBuffer& myApplication::getAudio(const std::string& audio_name){
    if (audio_name == "welcome_sound_buff"){
        return welcome_sound_buff_;
    }
}

sf::RenderWindow& myApplication::getWindow(){
    return window_;
}

sf::VideoMode& myApplication::getVideoMode(){
    return videomode_;
}

const std::string& myApplication::getCurrenScreenType(){
    return current_screen_type_;
}

myScreen& myApplication::getCurrentScreen(){
    if (current_screen_type_ == "welcome"){
        return welcome_screen_;
    }
    else if (current_screen_type_ == "end"){
        return end_screen_;
    }
}

sf::Vector2f& myApplication::getWindowOrigin(){
    return window_origin_;
}