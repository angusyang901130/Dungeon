#include "Player.h"

Player::Player(){
    // empty for now
}

Player::Player(string name, int health, int attack, int defense, int money):GameCharacter(name, "player", health, attack, defense){
    this->money = money;
}

void Player::addItem(Item* item){
    this->inventory.push_back(item);
}

void Player::increaseStates(int delta_health, int delta_attack, int delta_defense){
    // the maxhealth needed to be checked while adding health, needed to be implemented
    this->setCurrentHealth(getCurrentHealth()+delta_health);

    if(this->getCurrentHealth() < 0){
        this->setCurrentHealth(0);
    }

    this->setAttack(getAttack()+delta_attack);
    this->setDefense(getDefense()+delta_defense);
}

void Player::setInventory(vector<Item*> inventory){
    this->inventory = inventory;
}

vector<Item*> Player::getInventory(){
    return this->inventory;
}

void Player::setCurrentRoom(Room* currentRoom){
    this->currentRoom = currentRoom;
}

Room* Player::getCurrentRoom(){
    return this->currentRoom;
}

void Player::setPreviousRoom(Room* previousRoom){
    this->previousRoom = previousRoom;
}

Room* Player::getPreviousRoom(){
    return this->previousRoom;
}

void Player::setMoney(int money){
    this->money = money;
}

int Player::getMoney(){
    return this->money;
}

void Player::changeRoom(Room* room){
    this->previousRoom = this->currentRoom;
    this->currentRoom = room;
}

void Player::removeItem(int num){
    this->inventory.erase(this->inventory.begin()+num);
}

Item* Player::getItem(int num){
    return this->inventory[num];
}

void Player::listItem(){
    for(unsigned i = 0; i < this->inventory.size(); i++){
        cout << "<" << i << ">" << this->inventory[i]->getName() << endl;
        cout << "Type: " << this->inventory[i]->getTag() << endl;
        cout << "H: " << this->inventory[i]->getHealth() << endl;
        cout << "A: " << this->inventory[i]->getAttack() << endl;
        cout << "D: " << this->inventory[i]->getDefense() << endl;
    }
}

void Player::setPet(Item* pet){
    this->pet = pet;
}

Item* Player::getPet(){
    return this->pet;
}

void Player::setWeapon(Item* weapon){
    this->weapon = weapon;
}

Item* Player::getWeapon(){
    return this->weapon;
}

void Player::setDefeatNum(int num){
    this->defeatNum = num;
}

int Player::getDefeatNum(){
    return this->defeatNum;
}

void Player::changeWeapon(Item* weapon){
    this->weapon = weapon;
}

bool Player::triggerEvent(Object* object){
    cout << "Your status:" << endl;
    cout << "A: " << this->getAttack() << " D: " << this->getDefense() << " H: " << this->getCurrentHealth() << "/" << this->getMaxHealth() <<  " $: " << this->getMoney();
    cout << endl;
    return true;
}
