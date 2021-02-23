#include "pacMan.h"

pacMan::pacMan(){
    score_ = 0;
    num_lives_ = 5;   //do not hard-code this here
}

pacMan::pacMan(std::vector <int>& level, tileMap& tile_map, const std::string& texture_name, myApplication& app) : movable(level, tile_map, "pacman_right_1", app){
    score_ = 0;
    num_lives_ = 5;
}

void pacMan::updateLives(){
    num_lives_--;
}

void pacMan::updateScore(){
    score_ += 5;
}

void pacMan::updateScore(int add_score){
    score_ += add_score;
}

void pacMan::resetScore(){
    score_ = 0;
}

void pacMan::resetLives(){
    num_lives_ = 5;
}

const int pacMan::getLivesCount(){
    return num_lives_;
}

const long long pacMan::getScore(){
    return score_;
}
