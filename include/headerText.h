#ifndef HEADER_TEXT_H
#define HEADER_TEXT_H

#include <SFML/Graphics.hpp>
#include <string>

//class for rendering text on the screens

class headerText : public sf::Text{
    private:
        sf::Text text_;
        std::string current_alignment_;
    public:
        headerText();
        headerText(const std::string&, const int, const sf::Font&, const sf::Color&, const std::string&);
        void setAlignment(const std::string&);
        void textCreate(const std::string&, const int, sf::Font&, const sf::Color&, const std::string&) ;
        void updateOrigin();
        sf::Text& getText();
        sf::Vector2f& getOrigin();
        std::string getCurrentAlignment();
        void Log();
};

#endif //HEADER_TEXT_H