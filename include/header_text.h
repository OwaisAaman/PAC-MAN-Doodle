#ifndef HEADER_TEXT_H
#define HEADER_TEXT_H

#include <SFML/Graphics.hpp>
#include <string>

class header_text : public sf::Text{
    public:
        sf::Text m_text;
        void setAlignment(int position);
        header_text(const std::string& str, const int text_size, const sf::Font& font, const sf::Color& color, const int position);
};

#endif //HEADER_TEXT_H