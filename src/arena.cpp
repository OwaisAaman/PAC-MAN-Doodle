#include "arena.h"
#include "enemy.h"
#include "pacMan.h"
#include "movable.h"

arena::arena(){}

void arena::loadPacMan(myApplication& app){
    pac_man_ = pacMan(app);
}

void arena::loadEnemies(myApplication& app){
    enemy_blinky_ = enemy(app, "ghost_blinky", "level 1", 1);
    enemy_blue_ = enemy(app, "ghost_blue_ghost", "level 1", 1);
    enemy_clyde_ = enemy(app, "ghost_clyde", "level 1", 1);
    enemy_inky_ = enemy(app, "ghost_inky", "level 1", 1);
    enemy_pinky_ = enemy(app, "ghost_pinky", "level 1", 1);
}

void arena::loadAll(myApplication& app){
    loadPacMan(app);
    loadEnemies(app);
}

void arena::moveAll(){
    pac_man_.move();
    enemy_blinky_.autoMove();
    enemy_blue_.autoMove();
    enemy_clyde_.autoMove();
    enemy_inky_.autoMove();
    enemy_pinky_.autoMove();
}

void arena::drawAll(myApplication& app){
    app.getWindow().draw(pac_man_.getSprite());
    app.getWindow().draw(enemy_blinky_.getSprite());
    app.getWindow().draw(enemy_blue_.getSprite());
    app.getWindow().draw(enemy_clyde_.getSprite());
    app.getWindow().draw(enemy_inky_.getSprite());
    app.getWindow().draw(enemy_pinky_.getSprite());
}

pacMan& arena::getPacMan(){
    return pac_man_;
}

enemy& arena::getEnemy(const std::string& name){
    if (name == "ghost_blinky"){
        return enemy_blinky_;
    }
    else if (name == "ghost_blue_ghost"){
        return enemy_blue_;
    }
    else if (name == "ghost_clyde"){
        return enemy_clyde_;
    }
    else if (name == "ghost_inky"){
        return enemy_inky_;
    }
    else if (name == "ghost_pinky"){
        return enemy_pinky_;
    }
}