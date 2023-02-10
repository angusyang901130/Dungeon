#include "Room.h"

Room::Room(){
    // empty for now
}

Room::Room(bool isExit, int index, vector<Object*> objects){
    this->isExit = isExit;
    this->index = index;
    this->objects = objects;
}

void Room::popObject(Object* object){
    for(unsigned i = 0; i < this->objects.size(); i++){

        if(this->objects[i]->getName() == object->getName()){
            objects.erase(this->objects.begin()+i);
        }

    }
}

void Room::setUpRoom(Room* upRoom){
    this->upRoom = upRoom;
}

void Room::setDownRoom(Room* downRoom){
    this->downRoom = downRoom;
}

void Room::setLeftRoom(Room* leftRoom){
    this->leftRoom = leftRoom;
}

void Room::setRightRoom(Room* rightRoom){
    this->rightRoom = rightRoom;
}

Room* Room::getUpRoom(){
    return this->upRoom;
}

Room* Room::getDownRoom(){
    return this->downRoom;
}

Room* Room::getLeftRoom(){
    return this->leftRoom;
}

Room* Room::getRightRoom(){
    return this->rightRoom;
}

void Room::setObjects(vector<Object*> objects){
    this->objects = objects;
}

vector<Object*> Room::getObjects(){
    return this->objects;
}

void Room::setIndex(int index){
    this->index = index;
}

int Room::getIndex(){
    return this->index;
}

void Room::setIsExit(bool isExit){
    this->isExit = isExit;
}

bool Room::getIsExit(){
    return this->isExit;
}

void Room::addObject(Object* object){
    this->objects.push_back(object);
}

void Room::replaceObject(int num, Object* object){
    this->objects[num] = object;
}
