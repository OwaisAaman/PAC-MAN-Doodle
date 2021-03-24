#ifndef PAC_MAN_H
#define PAC_MAN_H

#include "movable.h"

class myApplication;

class pacMan : public movable{
    private :
        long long   score_;
        int         small_pill_score_;
        int         big_pill_score_;
    public :
        pacMan();
        pacMan(const std::vector <int>&, const tileMap&, const std::string&, const myApplication&, const bool, const int);
        void initPacMan();
        void updateScore();
        void updateScore(const int);
        void resetScore();
        void setNewTexture(const myApplication&, const std::string&);
        void glow(const std::string& event);
        void kill();
        const long long getScore();
        const int getLivesCount();
};

#endif //PAC_MAN_H