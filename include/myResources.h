#ifndef MY_RESOURCES_H
#define MY_RESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class myResources{
    private:
        sf::Font pac_font_;
        sf::Font regular_font_;
        sf::Texture welcome_texture_;
        sf::Texture end_texture_;
        sf::Texture game_texture_;
        sf::Texture pacman_right_1_;
        sf::Texture pacman_left_1_;
        sf::Texture pacman_up_1_;
        sf::Texture pacman_down_1_;
        sf::Texture ghost_blinky_;
        sf::Texture ghost_blue_ghost_;
        sf::Texture ghost_clyde_;
        sf::Texture ghost_inky_;
        sf::Texture ghost_pinky_;
        sf::Texture food_dot_;
        sf::Texture game_;
        sf::SoundBuffer welcome_sound_buff_;
        sf::SoundBuffer end_sound_buff_;
        sf::SoundBuffer eat_sound_buff_;
        sf::SoundBuffer die_sound_buff_;
        sf::SoundBuffer interval_sound_buff_;
        std::vector <int> level_1_;
        std::vector <int> level_2_;
        std::vector <int> level_3_;
        std::vector <int> level_4_;
        std::vector <int> level_5_;

    public:
        void loadFont(sf::Font&, const std::string&);
        void loadAllFonts();
        void loadTexture(sf::Texture&, const std::string&);
        void loadAllTextures();
        void loadAudio(sf::SoundBuffer&, const std::string&);
        void loadAllAudio();
        void loadLevel(std::vector <int>&, const std::string&);
        void loadAllLevels();
        std::vector <int> getLevel(int);
        sf::Font& getFont(const std::string&);
        sf::Texture& getTexture(const std::string&);
        sf::SoundBuffer& getAudio(const std::string&);
        void loadAllResources();

};

#endif //MY_RESOURCES_H