#ifndef MY_SCREEN_H
#define MY_SCREEN_H

#include "headerText.h"
#include <vector>
#include <string>

class myApplication;

class myScreen {
    private:
        headerText top_row_;
        headerText bottom_row_;
        headerText middle_row_;
        sf::Sprite sprite_;
        std::string screen_type_;
        sf::Vector2u window_size_;
        sf::Vector2f scale_;
    public:
        myScreen();
        myScreen(std::string, sf::RenderWindow&, sf::Font&, sf::Font&);
        void setScreenType(const std::string&);
        void setWindow(sf::RenderWindow&);
        void updateScreen(myApplication&);
        void screenInit(sf::RenderWindow&, const std::string&);
        void setSprite(sf::Texture&, const float, const float);
        void setText(headerText&, const std::string& , const int, sf::Font&, const sf::Color&, const std::string&, const float);
        void renderScreen(const std::string&, myApplication&);
        void drawScreen(myApplication&);
        sf::Vector2u& getWindowSize();

};

#endif // MY_SCREEN_H