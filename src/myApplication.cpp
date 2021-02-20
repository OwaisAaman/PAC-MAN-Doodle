#include "myApplication.h"
#include <iostream>

myApplication::myApplication(){}

void myApplication::setDefaultWindow(const int width, const int height){
    default_window_width_ = width;
    default_window_height_ = height;
}

void myApplication::appInit(const int width, const int height){
    setDefaultWindow(width, height);
    resources_.loadAllResources();
    configureWindow(default_window_width_, default_window_height_);
    loadAllScreens();
    updateWindowOrigin();
    loadAllMaps();
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

void myApplication::loadMap(tileMap& map_name, const std::string& level_name, sf::Vector2u tile_size, const int x_tiles, const int y_tiles, myApplication& app){
    map_name.loadMap(level_name, tile_size, x_tiles, y_tiles, app);
}

void myApplication::loadAllMaps(){
    loadMap(map_0_, "wire-frame", sf::Vector2u(28, 28) , 25, 29, *this);
    loadMap(map_1_, "level_1", sf::Vector2u(28, 28) , 25, 29, *this);
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
    window_origin_ = {(float)window_.getSize().x / 2, (float)window_.getSize().y / 2};
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
    return resources_.getFont(font_name);
}

sf::Texture& myApplication::getTexture(const std::string& texture_name){
    return resources_.getTexture(texture_name);
}

sf::SoundBuffer& myApplication::getAudio(const std::string& audio_name){
    return resources_.getAudio(audio_name);
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

int myApplication::getDefaultWindowWidth(){
    return default_window_width_;
}

int myApplication::getDefaultWindowHeight(){
    return default_window_height_;
}

const std::vector <int>& myApplication::getLevel(){
    return resources_.getLevel();
}

tileMap& myApplication::getMap(const std::string& level_name){
    if (level_name == "wire-frame"){
        return map_0_;
    }
    else if (level_name == "level 1"){
        return map_1_;
    }
}