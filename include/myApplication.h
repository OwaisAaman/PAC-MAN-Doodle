#ifndef MY_APPLICATION_H
#define MY_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "myScreen.h"
#include "myResources.h"
#include <vector>
#include "tileMap.h"


//not using a std::map container as that would require keeping a track of all the keys. 
//Even if the pre-known keys are added in the comments for referencing, it is possible that a new key might be 
//filled and might get lost and would require going through the entire code to search for the keys.

//class tileMap;

class myApplication {
    private:
        sf::RenderWindow window_;
        int default_window_width_;
        int default_window_height_;
        int current_level_;
        int max_level_;
        long long score_;
        long long high_score_;
        sf::VideoMode videomode_;
        sf::Vector2f window_origin_;
        sf::View view_;
        std::string current_screen_type_;
        sf::Vector2u min_window_size_;
        myResources resources_;
        myScreen welcome_screen_;
        myScreen pre_game_screen_;
        myScreen game_screen_;
        myScreen end_screen_;
        sf::Sound sound_;
        bool wait_;
    public:
        myApplication();
        void appInit(const int, const int);
        void setDefaultWindow(const int, const int);
        void configureWindow(const int, const int);
        void loadScreen(const std::string&);
        void loadAllScreens();
        void updateView();
        void drawScreen();
        void updateWindowOrigin();
        void setCurrentScreenType(const std::string&);
        void setCurrentLevel(int);
        void runApp();
        void checkWindowClosed(sf::Event&);
        void checkChangeScreen(sf::Event&);
        void checkPacManVelocity(sf::Event&);
        void checkPacManVelocity();
        void updateScores();
        void setMinWindowSize(sf::Vector2u);
        void resetApp();
        void checkLevelClear();
        void checkGameOver();
        void checkWindowFocus(sf::Event&);
        void setSound(const std::string&);
        const std::string& getCurrenScreenType(); 
        const int getCurrentLevel();
        sf::Font& getFont(const std::string&);
        sf::Texture& getTexture(const std::string&);
        sf::SoundBuffer& getAudio(const std::string&);
        sf::RenderWindow& getWindow();
        sf::VideoMode& getVideoMode();
        myScreen& getCurrentScreen();
        sf::Vector2f& getWindowOrigin();
        int getDefaultWindowHeight();
        int getDefaultWindowWidth();
        std::vector <int> getLevel(int);
        int getScore();
        int getHighScore();
        sf::Sound& getSound();
};


#endif //MY_APPLICATION_H