#ifndef PAC_MAN_H
#define PAC_MAN_H

#include "movable.h"
#include "myApplication.h"

class pacMan : public movable{
    private :
        long long score_;
    public :
        pacMan(myApplication& app);
        void updateScore();
        const long long getScore();
};

#endif //PAC_MAN_H