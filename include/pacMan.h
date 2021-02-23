#ifndef PAC_MAN_H
#define PAC_MAN_H

#include "movable.h"
#include "myApplication.h"

class pacMan : public movable{
    private :
        long long score_;
        int num_lives_;
    public :
        pacMan();
        pacMan(std::vector <int>&, tileMap&, const std::string&, myApplication&);
        void updateScore();
        void updateScore(int);
        void updateLives();
        void resetScore();
        void resetLives();
        const long long getScore();
        const int getLivesCount();

};

#endif //PAC_MAN_H