#ifndef PAC_MAN_H
#define PAC_MAN_H

#include "movable.h"

class myApplication;

class pacMan : public movable{
    private :
        long long score_;
        int num_lives_;
        int small_pill_score_;
        int big_pill_score_;
    public :
        pacMan();
        pacMan(std::vector <int>&, tileMap&, const std::string&, myApplication&, bool, int);
        void updateScore();
        void updateScore(int);
        void updateLives();
        void resetScore();
        void resetLives();
        void setNewTexture(myApplication&, const std::string&);
        void glow(const std::string& event);
        const long long getScore();
        const int getLivesCount();

};

#endif //PAC_MAN_H