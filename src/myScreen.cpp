#include "myScreen.h"
#include "myApplication.h" 
#include <iostream>
#include "arena.h"

myScreen::myScreen(){
    scale_ = sf::Vector2f(1.f, 1.f);
}

void myScreen::setScreenType(const std::string& type){
    screen_type_ = type;
}

void myScreen::updateScale(myApplication& app){
    scale_ = {app.getWindow().getSize().x / (float)app.getDefaultWindowWidth(), app.getWindow().getSize().y / (float)app.getDefaultWindowHeight()};
    window_size_ = app.getWindow().getSize();   
}

void myScreen::screenInit(myApplication& app, const std::string& type){
    setScreenType(type);
    updateScale(app);
}

void myScreen::updateScreen(myApplication& app){
    sf::Vector2u new_size = app.getWindow().getSize();
    if (new_size.x != window_size_.x || new_size.y != window_size_.y){
        updateScale(app);
        app.updateWindowOrigin();
        renderScreen(screen_type_, app);
    }
}

void myScreen::setText(headerText& text_row, const std::string& text, const int font_size, sf::Font& font, 
                      const sf::Color& color, const std::string& alignment, const float y_pos){
    text_row.textCreate(text, font_size, font, color, alignment);
    text_row.getText().setPosition(window_size_.x / 2, window_size_.y / 2);
    text_row.getText().setScale(scale_);
    text_row.getText().setPosition(window_size_.x / 2, y_pos * window_size_.y);
}

void myScreen::setSprite(myApplication& app, const std::string& texture_name, const float scale_x, const float scale_y){
    sf::Vector2f pre_scale = {scale_x * app.getDefaultWindowWidth() / app.getTexture(texture_name).getSize().x, scale_y * app.getDefaultWindowHeight() / app.getTexture(texture_name).getSize().y};
    sprite_.setScale(1, 1);
    app.getTexture(texture_name).setSmooth(true);
    sprite_.setTexture(app.getTexture(texture_name));
    sprite_.setOrigin(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);
    sprite_.scale(pre_scale);
    sprite_.setPosition(window_size_.x / 2, window_size_.y / 2);
    sprite_.scale(scale_);
}

void myScreen::renderScreen(const std::string& type, myApplication& app){
    if (type == "welcome"){
        setText(top_row_, "PAC MAN", 75, app.getFont("pac_font"), sf::Color::Yellow, "center", 0.08f);
        setText(middle_row_, "Press ENTER key to start", 40, app.getFont("regular_font"), sf::Color::Yellow, "center", 0.8f);
        setText(bottom_row_, "(Written in C++)", 20, app.getFont("regular_font"), sf::Color::Yellow, "center", 0.95f);
        setSprite(app, "welcome_texture", 0.7f, 0.4f);
    }
    else if (type == "pre_game"){
        setText(middle_row_, "Level 1", 40, app.getFont("regular_font"), sf::Color::Yellow, "center", 0.5f);
    }
    else if (type == "game"){
        setText(top_row_, "Score", 40, app.getFont("regular_font"), sf::Color::Yellow, "left", 0.03f);
        top_row_.getText().move(-game_arena_.getMap().getHOffset(), 0);
    }
    else if (type == "end"){
        setText(middle_row_, "Game Over", 50, app.getFont("pac_font"), sf::Color::Yellow, "center", 0.75f);
        setSprite(app, "end_texture", 0.2f, 0.2f);
    }
}

void myScreen::drawScreen(myApplication& app){
    app.getWindow().draw(top_row_.getText());
    app.getWindow().draw(middle_row_.getText());
    app.getWindow().draw(bottom_row_.getText());
    app.getWindow().draw(sprite_);
}

sf::Vector2u& myScreen::getWindowSize(){
    return window_size_;
}