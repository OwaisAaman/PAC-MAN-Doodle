#include "myApplication.h"
#include <iostream>

myApplication::myApplication(){}

void myApplication::setMinWindowSize(const sf::Vector2u size){
    min_window_size_ = size;
}

void myApplication::setDefaultWindow(const int width, const int height){
    default_window_width_ = width;
    default_window_height_ = height;
}

void myApplication::loadAScreen(myScreen& screen_object, const std::string& type){
    //loads a screen object in the memory given the type
    screen_object.screenInit(*this, type);
    screen_object.renderScreen(type, *this);
}

void myApplication::loadScreen(const std::string& type){
    if (type == "welcome")          {this->loadAScreen(welcome_screen_, type);}
    else if (type == "end")         {this->loadAScreen(end_screen_, type);}
    else if (type == "pre_game")    {this->loadAScreen(pre_game_screen_, type);}
    else if (type == "game")        {this->loadAScreen(game_screen_, type);}
}

void myApplication::loadAllScreens(){
    this->loadScreen("welcome");
    this->loadScreen("end");
    this->loadScreen("pre_game");
    this->loadScreen("game");
}

void myApplication::setCurrentScreenType(const std::string& type){
    current_screen_type_ = type;
}

void myApplication::setCurrentLevel(const int level){
    current_level_ = level;
}

void myApplication::configureWindow(const int screen_width, const int screen_height){
    videomode_.width = screen_width;
    videomode_.height = screen_height;
    window_.create(videomode_, "PAC-MAN");
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(12);
    this->setMinWindowSize(sf::Vector2u(screen_width, screen_height));
}

void myApplication::updateView(){
    view_.setCenter(window_.getSize().x / 2.f, window_.getSize().y / 2.f);
    view_.setSize(window_.getSize().x, window_.getSize().y);
    window_.setView(view_);
}

void myApplication::updateWindowOrigin(){
    window_origin_ = {(float)window_.getSize().x / 2, (float)window_.getSize().y / 2};
}

void myApplication::appInit(const int width, const int height){
    setDefaultWindow(width, height);
    resources_.loadAllResources();
    configureWindow(default_window_width_, default_window_height_);
    max_level_ = 5;
    this->setCurrentScreenType("welcome");
    this->setCurrentLevel(1);
    this->loadAllScreens();
    this->updateWindowOrigin();
    score_ = 0;
    high_score_ = 0;
    this->setSound("welcome_sound_buff");
    wait_ = false;
}

void myApplication::drawScreen(){
    //checks to avoid window being resized beyond the min threshold
    if (window_.getSize().x < min_window_size_.x){
        window_.setSize(sf::Vector2u(min_window_size_.x, window_.getSize().y));
    }
    if (window_.getSize().y < min_window_size_.y){
       window_.setSize(sf::Vector2u(window_.getSize().x, min_window_size_.y));
    }
    if (current_screen_type_ == "welcome"){welcome_screen_.drawScreen(*this);}
    else if (current_screen_type_ == "end"){end_screen_.drawScreen(*this);}
    else if (current_screen_type_ == "pre_game"){pre_game_screen_.drawScreen(*this);}
    else if (current_screen_type_ == "game"){game_screen_.drawScreen(*this);}
}

void myApplication::checkWindowClosed(const sf::Event& event){
    if (event.type == sf::Event::Closed){
        sound_.stop();
        window_.close();
    }
}

void myApplication::switchScreen(const std::string& new_screen, const std::string& sound_buffer){
    this->setCurrentScreenType(new_screen);
    this->loadScreen(current_screen_type_);
    this->setSound(sound_buffer);
}

void myApplication::checkChangeScreen(const sf::Event& event){
    //to check if a user has entered from one screen to another by pressing a key or by completing/failing a level
    if (current_screen_type_ == "welcome" && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
        this->switchScreen("pre_game", "interval_sound_buff");
    }
    else if (current_screen_type_ == "pre_game" && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
        setCurrentScreenType("game");
        loadScreen(current_screen_type_);
        sound_.stop();
        sound_.setBuffer(resources_.getAudio("eat_sound_buff"));
        sound_.setLoop(false);
    }
}

void myApplication::checkPacManVelocity(const sf::Event& event){
    //check if the pacman has an active velocity on the basis of triggered events
    if (current_screen_type_ == "game"){
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Up)         {game_screen_.setVelocity(*this, "Up");}
            else if (event.key.code == sf::Keyboard::Down)  {game_screen_.setVelocity(*this, "Down");}
            else if (event.key.code == sf::Keyboard::Right) {game_screen_.setVelocity(*this, "Right");}
            else if (event.key.code == sf::Keyboard::Left)  {game_screen_.setVelocity(*this, "Left");}
        }
        else if (event.type == sf::Event::KeyReleased){
            if (event.key.code == sf::Keyboard::Up)         {game_screen_.killVelocity("Up");}
            else if (event.key.code == sf::Keyboard::Down)  {game_screen_.killVelocity("Down");}
            else if (event.key.code == sf::Keyboard::Right) {game_screen_.killVelocity("Right");}
            else if (event.key.code == sf::Keyboard::Left)  {game_screen_.killVelocity("Left");}
        }
    }
}

void myApplication::checkPacManVelocity(){
    //check if the pacman has active velocity on the basis of real-time inputs
    if (current_screen_type_ == "game"){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))     {game_screen_.setVelocity(*this, "Left");}
        else                                                    {game_screen_.killVelocity("Left");}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))       {game_screen_.setVelocity(*this, "Up");}
        else                                                    {game_screen_.killVelocity("Up");}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))     {game_screen_.setVelocity(*this, "Down");}
        else                                                    {game_screen_.killVelocity("Down");}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    {game_screen_.setVelocity(*this, "Right");}
        else                                                    {game_screen_.killVelocity("Right");}
    }
}

void myApplication::setSound(const std::string& buffer_name){
    sound_.stop();
    sound_.setBuffer(resources_.getAudio(buffer_name));
    sound_.setLoop(true);
    sound_.play();
}

void myApplication::checkLevelClear(){
    if (current_screen_type_ == "game" && getCurrentScreen().getLevelClearStatus() == true){
        if (current_level_ == max_level_){
            this->switchScreen("end", "end_sound_buff");
        }
        else {
            this->updateScores();
            this->setCurrentLevel(current_level_ + 1);
            this->switchScreen("pre_game", "interval_sound_buff");
        }
    }
}

void myApplication::checkGameOver(){
    if (current_screen_type_ == "game" && getCurrentScreen().getGameOverStatus() == true){
        this->switchScreen("end", "interval_sound_buff");
    }
}

void myApplication::updateScores(){
    score_ += getCurrentScreen().getScore();
    if (score_ > high_score_)   {high_score_ = score_;}
}

void myApplication::checkWindowFocus(const sf::Event& event){
    if (event.type == sf::Event::LostFocus)     {wait_ = true;}
    if (event.type == sf::Event::GainedFocus)   {wait_ = false;}
}

void myApplication::runApp(){
    appInit(1200, 900);
    while (window_.isOpen()){
        sf::Event event;
        while (window_.pollEvent(event)){
            checkWindowClosed(event);
            checkChangeScreen(event);
            checkWindowFocus(event);
        }
        if (wait_){
            sf::sleep(sf::seconds(0.1f));
        }
        if (!wait_){
            checkPacManVelocity();
            checkGameOver();
            checkLevelClear();
            window_.clear();
            updateView();
            getCurrentScreen().updateScreen(*this);
            drawScreen();
            window_.display();
        }
    }
}

void myApplication::resetApp(){
    score_ = 0;
}

const sf::Font& myApplication::getFont(const std::string& font_name){
    return resources_.getFont(font_name);
}

const sf::Texture& myApplication::getTexture(const std::string& texture_name) const{
    return resources_.getTexture(texture_name);
}

const sf::SoundBuffer& myApplication::getAudio(const std::string& audio_name){
    return resources_.getAudio(audio_name);
}

sf::RenderWindow& myApplication::getWindow(){
    return window_;
}

sf::VideoMode& myApplication::getVideoMode(){
    return videomode_;
}

const std::string& myApplication::getCurrenScreenType(){
    return current_screen_type_;
}

myScreen& myApplication::getCurrentScreen(){
    if (current_screen_type_ == "welcome")          {return welcome_screen_;}
    else if (current_screen_type_ == "end")         {return end_screen_;}
    else if (current_screen_type_ == "pre_game")    {return pre_game_screen_;}
    else if (current_screen_type_ == "game")        {return game_screen_;}
}

sf::Vector2f& myApplication::getWindowOrigin(){
    return window_origin_;
}

int myApplication::getDefaultWindowWidth(){
    return default_window_width_;
}

int myApplication::getDefaultWindowHeight(){
    return default_window_height_;
}

const std::vector <int> myApplication::getLevel(const int level){
    return resources_.getLevel(level);
}

const int myApplication::getCurrentLevel(){
    return current_level_;
}

int myApplication::getScore(){
    return score_;
}

int myApplication::getHighScore(){
    return high_score_;
}

sf::Sound& myApplication::getSound(){
    return sound_;
}