#include "aStar.h"
#include <map>
#include <string>
#include <iostream>

aStar::Node::Node(){
    parent = nullptr;
}

aStar::pathFind::pathFind(){}

aStar::Node aStar::pathFind::getNodeFromIndex(int& index, tileMap& map, aStar::Node* source){
    aStar::Node node;
    node.parent = source;
    node.index = index;
    node.is_source = false;
    node.is_destination = false;
    node.is_open = true;

    if (index == source_index_){
        node.is_source = true;
        node.g = 0;
    }
    else{
        node.g = 1 + source->g;
    }
    
    if (index == destination_index_){
        node.is_destination = true;
        node.h = 0;
    }
    else{
        node.h = aStar::pathFind::getDistance(index, destination_index_, map);
    }

    return node;
}

int aStar::pathFind::getDistance(int& source, int& destination, tileMap& map){
    int row_s = map.getRow(source);
    int col_s = map.getCol(source, row_s);

    int row_d = map.getRow(destination);
    int col_d = map.getCol(destination, row_d);

    return abs(row_s - row_d) + abs(col_s - col_d);
}

int aStar::pathFind::getTop(int index, tileMap& map, std::vector <int>& map_array){
    int ans = index - map.getNumTiles().x;
    if (ans >= 0 && map_array[ans] != 1){
        return ans;
    }
    else {
        return -1;
    }
}

int aStar::pathFind::getBottom(int index, tileMap& map, std::vector <int>& map_array){
    int ans = index + map.getNumTiles().x;
    if (ans < (int) map_array.size() && map_array[ans] != 1){
        return ans;
    }
    else {
        return -1;
    }
}

int aStar::pathFind::getLeft(int index, tileMap& map, std::vector <int>& map_array){
    int row = map.getRow(index);
    int col = map.getCol(index, row);
    int ans = index - 1;
    if (col > 0 && map_array[ans] != 1){
        return ans;
    }
    else {
        return -1;
    }
}

int aStar::pathFind::getRight(int index, tileMap& map, std::vector <int>& map_array){
    int row = map.getRow(index);
    int col = map.getCol(index, row);
    int ans = index + 1;
    if (col < map.getNumTiles().x - 1 && map_array[ans] != 1){
        return ans;
    }
    else {
        return -1;
    }
}

std::vector <int> aStar::pathFind::getPath(int& source, const int destination, tileMap& map, std::vector <int>& map_array){
    std::vector <aStar::Node> open_set;
    std::map <int, aStar::Node*> index_map;

    source_index_ = source;
    destination_index_ = destination;

    //std::cout << "the source and destination obtained from the enemy class is " << source_index_ << " " << destination_index_ << std::endl;

    aStar::Node source_node;
    source_node = getNodeFromIndex(source_index_, map, &source_node);
    source_node.parent = nullptr;
    open_set.push_back(source_node);
    index_map[source_node.index] = &(open_set.back());
    if (source_node.index == -1){
        std::cout << "created a source node with -1 index " << std::endl;
    }
    //std::cout << "the source node address is " << index_map[source_node.index] << std::endl;

    auto current_it = open_set.begin();
    while (!open_set.empty()){

        current_it = open_set.begin();
        int min_cost = 10000000;
        int traversed_nodes = 0;
        for (auto it = open_set.begin(); it!= open_set.end(); it++){
            if (it->is_open == false){
                continue;
            }
            else if (it->g + it->h < min_cost){
                current_it = it;
                min_cost = it->g + it->h;
                ++traversed_nodes;
            }
        }

        if (current_it->is_destination || traversed_nodes == 0){    //break the loop if all the nodes are closed or the destination in reached
            break;
        }
        
        //std::cout << "the source node address is " << &(*current_it) << std::endl;
        current_it->is_open = false;
        //std::cout << "calling neighbors" << std::endl;
        std::vector <int> neighbors;
        neighbors.push_back(getTop(current_it->index, map, map_array));
        neighbors.push_back(getBottom(current_it->index, map, map_array));
        neighbors.push_back(getLeft(current_it->index, map, map_array));
        neighbors.push_back(getRight(current_it->index, map, map_array));

        int cost = current_it->g + 1;
        

        for (int i = 0; i < 4; i++){
            //std::cout << "the neighbors of " << current_it->index << " are " << neighbors[i] << std::endl;
            if (neighbors[i] == -1 ){   //|| index_map[neighbors[i]]->is_open == false
                continue;
            }
            else if (index_map[neighbors[i]] == 0){
                aStar::Node new_node;
                new_node = getNodeFromIndex(neighbors[i], map, &(*current_it));
                open_set.push_back(new_node);
                index_map[neighbors[i]] = &(open_set.back());
                //std::cout << "the parent address is " << &(*current_it) << std::endl;
                if (neighbors[i] == -1){
                    std::cout << "created a node with -1 index " << std::endl;
                }
             }
            else if (index_map[neighbors[i]]->is_open == false){
                continue;
            }
            else if (cost < index_map[neighbors[i]]->g){
                index_map[neighbors[i]]->g = cost;
                index_map[neighbors[i]]->parent = &(*current_it);
                //std::cout << "the address is " << index_map[neighbors[i]]->parent << std::endl;
            }
        }

    }

    for (int i = 0; i < (int)open_set.size(); i++){
        if (open_set[i].parent == 0){
            std::cout << "there exists a node with no parent" << std::endl;
            std::cout << "the index of such node is " << open_set[i].index << std::endl;
        }
    }

    std::vector <int> index_path;
    index_path.push_back(current_it->index);
    aStar::Node* current = current_it->parent;
    while (current != nullptr){
        //std::cout << "looping to find the path" << std::endl;
        index_path.push_back(current->index);
        //std::cout << current->index << std::endl;
        if (current->index < 0 || current->index >= (int)map_array.size()){
            std::cout << "error" << std::endl;
            //std::cout << current->index << std::endl;
            std::cout << current << std::endl;
        }
        current = current->parent;
    }
    //std::cout << "the size of the path is " << index_path.size() << std::endl;

    return index_path;
}