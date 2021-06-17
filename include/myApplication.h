#ifndef MY_APPLICATION_H
#define MY_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "myScreen.h"
#include "myResources.h"
#include <vector>
#include "tileMap.h"

class myApplication {
    private:
        
        int                 default_window_width_;
        int                 default_window_height_;
        int                 current_level_;
        int                 max_level_;
        long long           score_;
        long long           high_score_;
        bool                wait_;
        sf::RenderWindow    window_;
        sf::VideoMode       videomode_;
        sf::Vector2f        window_origin_;
        sf::View            view_;
        std::string         current_screen_type_;
        sf::Vector2u        min_window_size_;
        myResources         resources_;
        myScreen            welcome_screen_;
        myScreen            pre_game_screen_;
        myScreen            game_screen_;
        myScreen            end_screen_;
        sf::Sound           sound_;
    public:
        myApplication();
        void appInit(const int, const int);
        void setDefaultWindow(const int, const int);
        void configureWindow(const int, const int);
        void loadAScreen(myScreen&, const std::string&);
        void loadScreen(const std::string&);
        void loadAllScreens();
        void updateView();
        void drawScreen();
        void updateWindowOrigin();
        void setCurrentScreenType(const std::string&);
        void setCurrentLevel(int);
        void runApp();
        void checkWindowClosed(const sf::Event&);
        void switchScreen(const std::string&, const std::string&, bool, bool);
        void checkChangeScreen(const sf::Event&);
        void checkPacManVelocity(const sf::Event&);
        void checkPacManVelocity();
        void updateScores();
        void setMinWindowSize(sf::Vector2u);
        void resetApp();
        void checkLevelClear();
        void checkGameOver();
        void checkWindowFocus(const sf::Event&);
        void setSound(const std::string&, bool, bool);
        const std::string& getCurrenScreenType() const; 
        const int getCurrentLevel() const;
        const sf::Font& getFont(const std::string&);
        const sf::Texture& getTexture(const std::string&) const;
        const sf::SoundBuffer& getAudio(const std::string&) const;
        sf::RenderWindow& getWindow();
        const sf::RenderWindow& getWindow() const;
        const sf::VideoMode& getVideoMode() const;
        myScreen& getCurrentScreen();
        const sf::Vector2f& getWindowOrigin() const;
        const int getDefaultWindowHeight() const;
        const int getDefaultWindowWidth() const;
        std::vector <int> getLevel(const int) const;
        int getScore() const;
        int getHighScore() const;
        sf::Sound& getSound();
};

#endif //MY_APPLICATION_H