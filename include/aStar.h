#ifndef A_STAR_H
#define A_STAR_H

#include "arena.h"
#include <algorithm>
#include <vector>
#include <set>

namespace aStar
{
    struct Node{
        int index;
        int g, h;
        bool is_source;
        bool is_destination;
        bool is_open;
        Node* parent;
        Node();
        int getCost();    
    };

    class pathFind{
        private:
            int source_index_;
            int destination_index_;
        public:    
            pathFind();
            aStar::Node getNodeFromIndex(int&, tileMap&, aStar::Node*);
            int getDistance(int&, int&, tileMap&);
            int getTop(int, tileMap&, std::vector <int>&);
            int getBottom(int, tileMap&, std::vector <int>&);
            int getRight(int, tileMap&, std::vector <int>&);
            int getLeft(int, tileMap&, std::vector <int>&);
            std::vector <int> getPath(int&, int, tileMap&, std::vector <int>&);

    };
} // namespace aStar


#endif //A_STAR_H