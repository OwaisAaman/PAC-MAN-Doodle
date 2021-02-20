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
        sf::VideoMode videomode_;
        sf::Vector2f window_origin_;
        sf::View view_;
        std::string current_screen_type_;
        myResources resources_;
        myScreen welcome_screen_;
        myScreen game_screen_;
        myScreen end_screen_;
        tileMap map_0_;
        tileMap map_1_;
    public:
        myApplication();
        void appInit(const int, const int);
        void setDefaultWindow(const int, const int);
        void configureWindow(const int, const int);
        void loadScreen(const std::string&);
        void loadAllScreens();
        void loadMap(tileMap&, const std::string&, sf::Vector2u, const int, const int, myApplication&);
        void loadAllMaps();
        void updateView();
        void drawScreen();
        void updateWindowOrigin();
        void setCurrentScreenType(const std::string&);
        void app_run();
        const std::string& getCurrenScreenType(); 
        sf::Font& getFont(const std::string&);
        sf::Texture& getTexture(const std::string&);
        sf::SoundBuffer& getAudio(const std::string&);
        sf::RenderWindow& getWindow();
        sf::VideoMode& getVideoMode();
        myScreen& getCurrentScreen();
        sf::Vector2f& getWindowOrigin();
        int getDefaultWindowHeight();
        int getDefaultWindowWidth();
        const std::vector <int>& getLevel();
        tileMap& getMap(const std::string&);
};


#endif //MY_APPLICATION_H