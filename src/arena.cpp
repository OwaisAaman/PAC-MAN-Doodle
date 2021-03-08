#include "arena.h"
#include <iostream>
#include "myApplication.h"

arena::arena(){
    map_ = tileMap();
    arena_food_count_ = 0;
    level_clear_ = false;
    freeze_enemies_ = false;
    already_frozen_ = false;
    pacman_lives_ = 5;
}

void arena::setArenaMapArray(myApplication& app){
    arena_map_array_ = app.getLevel(app.getCurrentLevel());
}

void arena::loadArenaMap(myApplication& app){
    map_.loadMap(arena_map_array_, sf::Vector2u(32, 32) , 21, 25, app);
}

void arena::arenaInit(myApplication& app){
    setArenaMapArray(app);
    loadArenaMap(app);
    loadAllMovables(app);
    loadPacManVertices();
    updateFoodCount();
    refresh_map_ = false;
    level_clear_ = false;
    freeze_enemies_ = false;
    already_frozen_ = false;
    pacman_texture_ = app.getTexture("pacman_right_1");
    pacman_texture_.setSmooth(true);
    pacman_dead_.setBuffer(app.getAudio("die_sound_buff"));
    pacman_lives_ = 2;
    game_over_ = false;
}

void arena::loadPacMan(myApplication& app){
    pac_man_ = pacMan(arena_map_array_, map_, "pacman_right_1", app, false, 325);
}

void arena::loadEnemies(myApplication& app){
    enemy_blinky_ = enemy(arena_map_array_, map_, "ghost_blinky", app, 1, false, 281, 30);
    enemy_clyde_ = enemy(arena_map_array_, map_, "ghost_clyde", app, 1, false, 283, 60);
    enemy_pinky_ = enemy(arena_map_array_, map_, "ghost_pinky", app, 1, false, 285, 90);
}

void arena::loadAllMovables(myApplication& app){
    loadPacMan(app);
    loadEnemies(app);
}

void arena::loadPacManVertices(){
    int lives = pacman_lives_;
    pacman_vertices_.resize(lives * 4);
    pacman_vertices_.setPrimitiveType(sf::Quads);

    double start_x = map_.getWOffset() / 2;
    double start_y = map_.getHOffset() / 2 + map_.getNumTiles().y * map_.getTileSize().y + 5;
    double offset = 10;
    
    for (int i = 0; i < lives; i++){
        sf::Vertex* quads = &pacman_vertices_[i * 4];
        quads[0].position = sf::Vector2f((start_x + i * map_.getTileSize().x + i * offset), (start_y));
        quads[1].position = sf::Vector2f((start_x + (i + 1) * map_.getTileSize().x + i * offset), (start_y));
        quads[2].position = sf::Vector2f((start_x + (i + 1) * map_.getTileSize().x + i * offset), (start_y + map_.getTileSize().y));
        quads[3].position = sf::Vector2f((start_x + i * map_.getTileSize().x + i * offset), (start_y + map_.getTileSize().y));

        quads[0].texCoords = sf::Vector2f(0, 0);
        quads[1].texCoords = sf::Vector2f(16, 0);
        quads[2].texCoords = sf::Vector2f(16, 16);
        quads[3].texCoords = sf::Vector2f(0, 16);
    }
}

void arena::drawPacManVertices(sf::RenderTarget& target){
    sf::RenderStates states;
    states.texture = &pacman_texture_;
    target.draw(pacman_vertices_, states);
}

void arena::updateFoodCount(){
    int fc = 0;
    for (int i = 0; i < (int)arena_map_array_.size(); i++){
        if (arena_map_array_[i] == 0){
            fc++;
        }
    }
    arena_food_count_ = fc;
}

void arena::updateFoodCount(int number){
    arena_food_count_ += number;
}

void arena::updateMap(myApplication& app){
    if (refresh_map_){
        loadArenaMap(app);
        loadPacManVertices();
        refresh_map_ = false;
    }
}

void arena::refreshMovables(sf::Vector2f& delta){
    pac_man_.setPosition(pac_man_.getPosition() + delta);
    enemy_blinky_.setPosition(enemy_blinky_.getPosition() + delta);
    enemy_clyde_.setPosition(enemy_clyde_.getPosition() + delta);
    enemy_pinky_.setPosition(enemy_pinky_.getPosition() + delta);
}

void arena::setRefreshMap(bool value){
    refresh_map_ = value;
}

void arena::moveAll(){
    pac_man_.move(map_, arena_map_array_);
    enemy_blinky_.autoMove(map_, arena_map_array_, false);
    enemy_clyde_.autoMove(map_, arena_map_array_, false);
    enemy_pinky_.autoMove(map_, arena_map_array_, false);
}

void arena::drawAll(myApplication& app){
    moveAll();
    pac_man_.updateActiveStatus();
    checkMap(app);
    unfreezeAllEnemies(app);
    freezeAllEnemies(app);
    checkAllCollisions();
    if (!game_over_){
        updateMap(app);
        respawnAllEnemies(app);
        respawnAllMovables(app);
        app.getWindow().draw(map_);
        drawPacManVertices(app.getWindow());
        app.getWindow().draw(pac_man_.getSprite());
        app.getWindow().draw(enemy_blinky_.getSprite());
        app.getWindow().draw(enemy_clyde_.getSprite());
        app.getWindow().draw(enemy_pinky_.getSprite());
    }
}

void arena::freezeEnemies(const int index){
    if (index == 2){
        freeze_enemies_ = true;
    }
}

void arena::freezeAllEnemies(myApplication& app){
    if (freeze_enemies_){
        enemy_blinky_.freeze(app);
        enemy_clyde_.freeze(app);
        enemy_pinky_.freeze(app);
        already_frozen_ = true;
        clock_.restart();
    }
}

void arena::unfreezeAllEnemies(myApplication& app){
    if (already_frozen_){
        sf::Time elapsed_time = clock_.getElapsedTime();
        if (elapsed_time.asSeconds() >= 40){
            enemy_blinky_.unfreeze(app, "ghost_blinky");
            enemy_clyde_.unfreeze(app, "ghost_clyde");
            enemy_pinky_.unfreeze(app, "ghost_pinky");
            already_frozen_ = false;
        }
    }
}

void arena::checkMap(myApplication& app){
    int pacman_index = pac_man_.getIndexFromPosition(map_);
    pac_man_.glow("normal");
    freeze_enemies_ = false;
    if ((arena_map_array_[pacman_index] == 0 || arena_map_array_[pacman_index] == 2) && pac_man_.getActiveStatus() == true){
        pac_man_.updateScore(arena_map_array_[pacman_index]);
        freezeEnemies(arena_map_array_[pacman_index]);
        if (arena_map_array_[pacman_index] == 0){
            pac_man_.glow("eat_small_pill");
        }
        else {
            pac_man_.glow("eat_big_pill");
        }
        arena_map_array_[pacman_index] = -1;
        refresh_map_ = true;
        updateFoodCount();
        app.getSound().play();
    }
    if (arena_food_count_ == 0){
        level_clear_ = true;
    }
}

void arena::checkCollision(enemy& enemy_name, int spawn_index){
    if (enemy_name.getAliveStatus()){
        int pacman_index = pac_man_.getIndexFromPosition(map_);
        int enemy_index = enemy_name.getIndexFromPosition(map_);
        if (pac_man_.getPosition().x == enemy_name.getPosition().x && pac_man_.getPosition().y == enemy_name.getPosition().y){
            if (enemy_name.getFreezeStatus()){
                killEnemy(enemy_name, spawn_index);
                pac_man_.glow("kill");
            }
            else {
                killPacMan();
            }
        }
    }
}

void arena::checkAllCollisions(){
    if (pac_man_.getAliveStatus()){
        checkCollision(enemy_blinky_, 281);
        checkCollision(enemy_clyde_, 283);
        checkCollision(enemy_pinky_, 285);
    }
}

void arena::killEnemy(enemy& enemy_name, int spawn_index){
    enemy_name.kill(map_, arena_map_array_, spawn_index);
    pac_man_.updateScore(200);
}

void arena::killPacMan(){
    pac_man_.kill();
    pacman_dead_.play();
    pacman_lives_--;
    if (pacman_lives_ < 0){
        game_over_ = true;
        pacman_dead_.stop();
    }
    else {
        loadPacManVertices();
    }
}

void arena::respawnEnemy(myApplication& app, enemy& enemy_name, const std::string& texture_name, int spawn_index){
    if (!enemy_name.getAliveStatus() && enemy_name.getReachedSpawnStatus()){
        enemy_name = enemy(arena_map_array_, map_, texture_name, app, 1, false, spawn_index, 10);
    }
}

void arena::respawnAllEnemies(myApplication& app){
    respawnEnemy(app, enemy_blinky_, "ghost_blinky", 281);
    respawnEnemy(app, enemy_clyde_, "ghost_clyde", 281);
    respawnEnemy(app, enemy_pinky_, "ghost_pinky", 281);
}

void arena::respawnAllMovables(myApplication& app){
    if (!pac_man_.getAliveStatus()){
        app.getWindow().clear();
        sf::sleep(sf::seconds(0.01f));
        pac_man_ = pacMan(arena_map_array_, map_, "pacman_right_1", app, false, 325);
        enemy_blinky_ = enemy(arena_map_array_, map_, "ghost_blinky", app, 1, false, 281, 25);
        enemy_clyde_ = enemy(arena_map_array_, map_, "ghost_clyde", app, 1, false, 283, 50);
        enemy_pinky_ = enemy(arena_map_array_, map_, "ghost_pinky", app, 1, false, 285, 75);
    }
}

void arena::setVelocity(myApplication& app, const std::string& direction){
    pac_man_.setVelocity(direction);
    pac_man_.setNewTexture(app, direction);
}

void arena::killVelocity(const std::string& direction){
    pac_man_.killVelocity(direction);
}

pacMan& arena::getPacMan(){
    return pac_man_;
}

enemy& arena::getEnemy(const std::string& name){
    if (name == "ghost_blinky"){
        return enemy_blinky_;
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

std::vector <int>& arena::getMapArray(){
    return arena_map_array_;
}

int arena::getFoodCount(){
    return arena_food_count_;
}

tileMap& arena::getMap(){
    return map_;
}

void arena::updateOffsets(myApplication& app){
    map_.updateWOffset(app);
    map_.updateHOffset(app);
}

bool arena::getLevelClearStatus(){
    return level_clear_;
}

bool arena::getGameOverStatus(){
    return game_over_;
}