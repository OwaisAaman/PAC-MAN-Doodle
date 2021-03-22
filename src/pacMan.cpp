#include "pacMan.h"
#include "myApplication.h"

pacMan::pacMan(){
    score_ = 0;
    small_pill_score_ = 5;
    big_pill_score_ = 50;
}

pacMan::pacMan(const std::vector <int>& level, const tileMap& tile_map, const std::string& texture_name, const myApplication& app, const bool random_spawn, const int spawn_index) : movable(level, tile_map, "pacman_right_1", app, random_spawn, spawn_index){
    *this = pacMan();
}

void pacMan::updateScore(){
    score_ += 5;
}

void pacMan::updateScore(const int index){
    if (index == 0)         {score_ += small_pill_score_;}
    else if (index == 2)    {score_ += big_pill_score_;}
    else                    {score_ += index;}
}

void pacMan::resetScore(){
    score_ = 0;
}

void pacMan::setNewTexture(const myApplication& app, const std::string& direction){
    if (direction == "Up")          {this->setTexture(app, "pacman_up_1");}
    else if (direction == "Down")   {this->setTexture(app, "pacman_down_1");}
    else if (direction == "Right")  {this->setTexture(app, "pacman_right_1");}
    else if (direction == "Left")   {this->setTexture(app, "pacman_left_1");}
}

void pacMan::glow(const std::string& event){
    if (event == "normal")              {this->getSprite().setColor(sf::Color::White);}
    else if (event == "eat_small_pill") {this->getSprite().setColor(sf::Color::Green);}
    else if (event == "eat_big_pill")   {this->getSprite().setColor(sf::Color::Red);}
    else if (event == "kill")           {this->getSprite().setColor(sf::Color::Red);}
}

void pacMan::kill(){
    this->glow("kill");
    is_alive_ = false;
}

const long long pacMan::getScore(){
    return score_;
}