#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item*> inventory;
    int money;
    Item* weapon;
    Item* pet;
    int defeatNum = 0;
public:
    Player();
    Player(string,int,int,int,int);
    void addItem(Item*);
    void increaseStates(int,int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item*>);
    void setMoney(int);
    void setPet(Item*);
    void setWeapon(Item*);
    Item* getWeapon();
    Item* getPet();
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item*> getInventory();
    int getMoney();
    void listItem();
    void removeItem(int);
    void changeWeapon(Item*);
    Item* getItem(int);
    void setDefeatNum(int);
    int getDefeatNum();
};

#endif // PLAYER_H_INCLUDED
