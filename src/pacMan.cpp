#include "pacMan.h"
#include "myApplication.h"

pacMan::pacMan(){
    score_ = 0;
    num_lives_ = 5;   //do not hard-code this here
    small_pill_score_ = 5;
    big_pill_score_ = 50;
}

pacMan::pacMan(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app, bool random_spawn, int spawn_index) : movable(level, tile_map, "pacman_right_1", app, random_spawn, spawn_index){
    score_ = 0;
    num_lives_ = 5;
    small_pill_score_ = 5;
    big_pill_score_ = 50;
}

void pacMan::updateLives(){
    num_lives_--;
}

void pacMan::updateScore(){
    score_ += 5;
}

void pacMan::updateScore(int index){
    if (index == 0){
        score_ += small_pill_score_;
    }
    else if (index == 2){
        score_ += big_pill_score_;
    }
    else {
        score_ += index;
    }
}

void pacMan::resetScore(){
    score_ = 0;
}

void pacMan::resetLives(){
    num_lives_ = 5;
}

void pacMan::setNewTexture(myApplication& app, const std::string& direction){
    if (direction == "Up"){
        setTexture(app, "pacman_up_1");
    }
    else if (direction == "Down"){
        setTexture(app, "pacman_down_1");
    }
    else if (direction == "Right"){
        setTexture(app, "pacman_right_1");
    }
    else if (direction == "Left"){
        setTexture(app, "pacman_left_1");
    }
}

const int pacMan::getLivesCount(){
    return num_lives_;
}

const long long pacMan::getScore(){
    return score_;
}
