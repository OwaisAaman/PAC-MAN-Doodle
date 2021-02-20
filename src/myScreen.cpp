#include "myScreen.h"
#include "headerText.h"
#include "myApplication.h" 
#include <iostream>

myScreen::myScreen(){}

void myScreen::setScreenType(const std::string& type){
    screen_type_ = type;
}

void myScreen::setWindow(sf::RenderWindow& window){
    window_size_ = window.getSize();
    scale_ = {window_size_.x / 1080.f, window_size_.y / 720.f};
}

void myScreen::screenInit(sf::RenderWindow& window, const std::string& type){
    setScreenType(type);
    setWindow(window);
}

void myScreen::updateScreen(myApplication& app){
    sf::Vector2u new_size = app.getWindow().getSize();
    if (new_size.x != window_size_.x || new_size.y != window_size_.y){
        window_size_ = new_size;
        scale_ = {window_size_.x / 1080.f, window_size_.y / 720.f};
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

void myScreen::setSprite(sf::Texture& texture, const float scale_x, const float scale_y){
    sf::Vector2f pre_scale = {scale_x * 1080 / texture.getSize().x, scale_y * 720 / texture.getSize().y};
    sprite_.setScale(1, 1);
    texture.setSmooth(true);
    sprite_.setTexture(texture);
    sprite_.setOrigin(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);
    sprite_.scale(pre_scale);
    sprite_.setPosition(window_size_.x / 2, window_size_.y / 2);
    sprite_.scale(scale_);
}

void myScreen::renderScreen(const std::string& type, myApplication& app){
    if (type == "welcome"){
        setText(top_row_, "PAC MAN", 75, app.getFont("pac_font"), sf::Color::Yellow, "center", 0.08f);
        setText(middle_row_, "Press ENTER key to start", 40, app.getFont("regular_font"), sf::Color::Yellow, "center", 0.8f);
        setText(bottom_row_, "(Written in C++ by agabhi017)", 20, app.getFont("regular_font"), sf::Color::Yellow, "center", 0.95f);
        setSprite(app.getTexture("welcome_texture"), 0.7f, 0.4f);
    }
    else if (type == "end"){
        setText(middle_row_, "Game Over", 50, app.getFont("pac_font"), sf::Color::Yellow, "center", 0.75f);
        setSprite(app.getTexture("end_texture"), 0.2f, 0.2f);
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