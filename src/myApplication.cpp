#include "myApplication.h"
#include <iostream>

myApplication::myApplication(){}

void myApplication::setMinWindowSize(sf::Vector2u size){
    min_window_size_ = size;
}

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
}

void myApplication::loadScreen(const std::string& type){
    if (type == "welcome"){
        welcome_screen_.screenInit(*this, type);
        welcome_screen_.renderScreen(type, *this);
    }
    else if (type == "end"){
        end_screen_.screenInit(*this, type);
        end_screen_.renderScreen(type, *this);
    }
    else if (type == "pre_game"){
        pre_game_screen_.screenInit(*this, type);
        pre_game_screen_.renderScreen(type, *this);
    }
    else if (type == "game"){
        game_screen_.screenInit(*this, type);
        game_screen_.renderScreen(type, *this);
    }
}

void myApplication::loadAllScreens(){
    this->loadScreen("welcome");
    this->loadScreen("end");
    this->loadScreen("pre_game");
    this->loadScreen("game");
}

void myApplication::setCurrentScreenType(const std::string& type){
    current_screen_type_ = type;
}

void myApplication::configureWindow(const int screen_width, const int screen_height){
    videomode_.width = screen_width;
    videomode_.height = screen_height;
    window_.create(videomode_, "PAC-MAN");
    window_.setFramerateLimit(60);
    setMinWindowSize(sf::Vector2u(900, 700));
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
    if (window_.getSize().x < min_window_size_.x){
        window_.setSize(sf::Vector2u(min_window_size_.x, window_.getSize().y));
    }
    if (window_.getSize().y < min_window_size_.y){
       window_.setSize(sf::Vector2u(window_.getSize().x, min_window_size_.y));
    }
    if (current_screen_type_ == "welcome"){
        welcome_screen_.drawScreen(*this);
    }
    else if (current_screen_type_ == "end"){
        end_screen_.drawScreen(*this);
    }
    else if (current_screen_type_ == "pre_game"){
        pre_game_screen_.drawScreen(*this);
    }
    else if (current_screen_type_ == "game"){
        game_screen_.drawScreen(*this);
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
    else if (current_screen_type_ == "pre_game"){
        return pre_game_screen_;
    }
    else if (current_screen_type_ == "game"){
        return game_screen_;
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

std::vector <int> myApplication::getLevel(const std::string& level_name){
    return resources_.getLevel(level_name);
}

