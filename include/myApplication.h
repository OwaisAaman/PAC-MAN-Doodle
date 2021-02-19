#ifndef MY_APPLICATION_H
#define MY_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "myScreen.h"
#include <vector>


//not using a std::map container as that would require keeping a track of all the keys. 
//Even if the pre-known keys are added in the comments for referencing, it is possible that a new key might be 
//filled and might get lost and would require going through the entire code to search for the keys.


class myApplication {
    private:
        sf::RenderWindow window_;
        sf::VideoMode videomode_;
        sf::Vector2f window_origin_;
        sf::Font pac_font_;
        sf::Font regular_font_;
        sf::Texture welcome_texture_;
        sf::Texture end_texture_;
        sf::Texture game_texture_;
        sf::SoundBuffer welcome_sound_buff_;
        sf::SoundBuffer end_sound_buff_;
        sf::SoundBuffer eat_sound_buff_;
        sf::SoundBuffer die_sound_buff_;
        sf::View view_;
        std::string current_screen_type_;
        myScreen welcome_screen_;
        myScreen game_screen_;
        myScreen end_screen_;
    public:
        myApplication();
        void appInit();
        void loadFont(sf::Font&, const std::string&);
        void loadAllFonts();
        void loadTexture(sf::Texture&, const std::string&);
        void loadAllTextures();
        void loadAudio(sf::SoundBuffer&, const std::string&);
        void loadAllAudio();
        void configureWindow(const int, const int);
        void loadScreen(const std::string&);
        void loadAllScreens();
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
};


#endif //MY_APPLICATION_H