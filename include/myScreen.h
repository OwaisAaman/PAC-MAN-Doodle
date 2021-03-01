#ifndef MY_SCREEN_H
#define MY_SCREEN_H

#include "headerText.h"
#include <vector>
#include <string>
#include "arena.h"

class myApplication;
//class arena;

class myScreen {
    private:
        arena game_arena_;
        headerText top_row_;
        headerText bottom_row_;
        headerText middle_row_;
        headerText top_row_2_;
        headerText left_row_1_;
        headerText left_row_2_;
        headerText right_row_1_;
        headerText right_row_2_;
        sf::Sprite sprite_;
        std::string screen_type_;
        sf::Vector2u window_size_; //keeping a copy here to check when to update the screen
        sf::Vector2f scale_;
    public:
        myScreen();
        myScreen(std::string, sf::RenderWindow&, sf::Font&, sf::Font&);
        void setScreenType(const std::string&);
        void updateScale(myApplication&);
        void updateScreen(myApplication&);
        void screenInit(myApplication&, const std::string&);
        void setSprite(myApplication&, const std::string&, const float, const float);
        void setText(headerText&, const std::string& , const int, sf::Font&, const sf::Color&, const std::string&, const float);
        void renderScreen(const std::string&, myApplication&);
        void drawScreen(myApplication&);
        sf::Vector2u& getWindowSize();

};

#endif // MY_SCREEN_H