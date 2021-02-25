#include "aStar.h"
#include <map>
#include <string>

astar::Node aStar::pathFind::getNodeFromIndex(const int index, tileMap& map, aStar::Node* source){
    astar::Node node;
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

int aStar::pathFind::getTop(int& index, tileMap& map, std::vector <int>& map_array){
    int ans = index - map.getNumTiles().x;
    if (ans >= 0 && map_array[ans] != 1){
        return ans;
    }
    else {
        return -1;
    }
}

int aStar::pathFind::getBottom(int& index, tileMap& map, std::vector <int>& map_array){
    int ans = index + map.getNumTiles().x;
    if (ans < (int) map_array.size() && map_array[ans] != 1){
        return ans;
    }
    else {
        return -1;
    }
}

int aStar::pathFind::getLeft(int& index, tileMap& map, std::vector <int>& map_array){
    int row = map.getRow(index);
    int col = map.getCol(index, row);
    int ans = index - 1;
    if (ans < (int) map_array.size() && col > 0 && col < map.getNumTiles().x - 1){
        return ans;
    }
    else {
        return -1;
    }
}

int aStar::pathFind::getRight(int& index, tileMap& map, std::vector <int>& map_array){
    int row = map.getRow(index);
    int col = map.getCol(index, row);
    int ans = index + 1;
    if (ans < (int) map_array.size() && col > 0 && col < map.getNumTiles().x - 1){
        return ans;
    }
    else {
        return -1;
    }
}

std::vector <int> aStar::pathFind::getPath(const int source, const int destination, tileMap& map, std::vector <int>& map_array){
    std::set <aStar::Node> open_set;
    std::map <int, aStar::Node*> index_map;

    source_index_ = source;
    destination_index_ = destination;

    aStar::Node source_node;
    source_node = getNodeFromIndex(source, map, &source_node);
    open_set.insert(&source_node);
    index_map[source_node.index] = &source_node;

    while (!open_set.empty()){
        aStar::Node* current_it = nullptr;
        int min_cost = 10000000;
        int travesred_nodes = 0;
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

        current_it->is_open = false;

        std::vector <int> neighbors;
        neighbors.push_back(getTop(current_it->index, map, map_array));
        neighbors.push_back(getBottom(current_it->index, map, map_array));
        neighbors.push_back(getLeft(current_it->index, map, map_array));
        neighbors.push_back(getRight(current_it->index, map, map_array));

        int cost = current_it->G + 1;

        for (int i = 0; i < 4; i++){
            if (neighbors[i] == -1 || index_map[neighbors[i]]->is_open == false){
                continue;
            }
            else if (index_map[neighbors[i]]== nullptr){
                aStar::Node new_node;
                new_node = getNodeFromIndex(neighbors[i], map, current_it);
                open_set.insert(new_node);
            }
            else if (cost < index_map[neighbors[i]]->g){
                index_map[neighbors[i]]->g = cost;
                index_map[neighbors[i]]->parent = current_it;
            }
        }

    }
    std::vector <int> index_path;
    while (current_it != nullptr){
        index_path.push_back(current_it->index);
        current_it = current_it->parent;
    }

    return index_path;
}