#include "header_text.h"

header_text::header_text(const std::string& str, const int text_size, const sf::Font& font, const sf::Color& color, const int position){
    m_text.setFont(font);
    m_text.setFillColor(color);
    m_text.setString(str);
    m_text.setCharacterSize(text_size);
    this->setAlignment(position);
}

//function for setting the aligment of the text relative to the window
//0--left
//1--center
//2--right

void header_text::setAlignment(int position) {
    sf::FloatRect bounds = m_text.getGlobalBounds();

    if (position == 1) {
        m_text.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    else if (position == 2) {
        m_text.setOrigin(bounds.width, bounds.top);
    }
    else {
        m_text.setOrigin(bounds.left, bounds.top);
    }
}