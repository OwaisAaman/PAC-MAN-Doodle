#include "headerText.h"
#include <iostream>

headerText::headerText(){}

headerText::headerText(const std::string& str, const int text_size, const sf::Font& font, const sf::Color& color, const std::string& alignment){
    text_.setFont(font);
    text_.setFillColor(color);
    text_.setString(str);
    text_.setCharacterSize(text_size);
    text_.setScale(1, 1);
    this->setAlignment(alignment);
}

void headerText::textCreate(const std::string& str, const int text_size, sf::Font& font, const sf::Color& color, const std::string& alignment) {
    *this = headerText(str, text_size, font, color, alignment);
}

void headerText::setAlignment(const std::string& alignment) {
    //updates the origin as per the alignment of the text
    sf::FloatRect bounds = text_.getGlobalBounds();
    current_alignment_ = alignment;

    if (alignment == "center") {
        text_.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    else if (alignment == "right") {
        text_.setOrigin(bounds.width, 0);
    }
    else if (alignment == "left"){
        text_.setOrigin(0, 0);
    }
}

void headerText::updateOrigin(){
    //method to update the origin when the window is resized
    this->setAlignment(this->current_alignment_);
}

sf::Text& headerText::getText(){
    return text_;
}

void headerText::Log(){
    std::cout << "The current alignment is " << current_alignment_ << std::endl;
    std::cout << "The bounding boxes are " << text_.getGlobalBounds().left << " " << text_.getGlobalBounds().top 
              << " " << text_.getGlobalBounds().width << " " <<text_.getGlobalBounds().height << std::endl; 
    std::cout << "The origin is set to " << text_.getOrigin().x << " " << text_.getOrigin().y << std::endl;
}