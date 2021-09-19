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
        arena           game_arena_;
        headerText      top_row_;
        headerText      bottom_row_;
        headerText      middle_row_;
        headerText      top_row_2_;
        headerText      left_row_1_;
        headerText      left_row_2_;
        headerText      right_row_1_;
        headerText      right_row_2_;
        sf::Sprite      sprite_;
        std::string     screen_type_;
        sf::Vector2u    window_size_; //keeping a copy here to check when to update the screen
        sf::Vector2f    scale_;
        long long       score_;
    public:
        myScreen();
        void setScreenType(const std::string&);
        void updateScale(const myApplication&);
        void updateScreen(myApplication&);
        void screenInit(myApplication&, const std::string&);
        void setSprite(const myApplication&, const std::string&, const float, const float);
        void setText(headerText&, const std::string& , const int, const sf::Font&, const sf::Color&, const std::string&, const float);
        void renderScreen(const std::string&, myApplication&);
        void drawScreen(myApplication&);
        void setVelocity(myApplication&, const std::string&);
        void killVelocity(const std::string&);
        void updatePacManLives(int count);
        sf::Vector2u& getWindowSize();
        const bool getLevelClearStatus();
        const bool getGameOverStatus();
        int getScore();
        int getPacManLives();
};

#endif // MY_SCREEN_H