#include "Record.h"

Record::Record(){
    // empty
}

void Record::savePlayer(Player* player, ofstream& fileout){

    // player status
    fileout << player->getName() << endl;
    fileout << player->getAttack() << endl;
    fileout << player->getDefense() << endl;
    fileout << player->getCurrentHealth() << endl;
    fileout << player->getMaxHealth() << endl;
    fileout << player->getMoney() << endl;

    // player's weapon and pet
    if(player->getWeapon() != NULL)  fileout << player->getWeapon()->getName() << endl;
        else fileout << "none" << endl;
    if(player->getPet() != NULL)  fileout << player->getPet()->getName() << endl;
        else fileout << "none" << endl;

    // player's inventory
    vector<Item*> inventory = player->getInventory();
    fileout << inventory.size() << endl;
    for(unsigned i = 0; i < inventory.size(); i++){
        fileout << inventory[i]->getName() << endl;
    }

    // player's last place
    fileout << player->getCurrentRoom()->getIndex() << endl;
    if(player->getPreviousRoom() == NULL){
        fileout << 0 << endl;
    }else fileout << player->getPreviousRoom()->getIndex() << endl;
}

void Record::saveRooms(vector<Room*>& rooms, ofstream& fileout){
    for(int i = 0; i < 9; i++){
        fileout << rooms[i]->getObjects().size() << endl;
    }
}

void Record::saveToFile(Player* player, vector<Room*>& rooms){
    ofstream outstream;
    outstream.open("Dungeon.txt");

    this->savePlayer(player, outstream);
    this->saveRooms(rooms, outstream);

    outstream.close();
}

void Record::loadPlayer(Player* player, vector<Room*>& rooms, ifstream& filein){
    int attack, defense, currentHealth, maxHealth, money, num;
    string itemName, weapon, pet, playerName;
    bool found = false;
    string c;
    // player name
    filein >> playerName;
    player->setName(playerName);

    // player status
    filein >> attack >> defense >> currentHealth >> maxHealth >> money;
    player->setAttack(attack);
    player->setDefense(defense);
    player->setCurrentHealth(currentHealth);
    player->setMaxHealth(maxHealth);
    player->setMoney(money);
    player->triggerEvent(nullptr);
    getline(filein, c);
    getline(filein, weapon);
    if(weapon == "no weapon"){
        Item* w = new Item("no weapon", 0, 0, 0, 0);
        player->setWeapon(w);
    }
    getline(filein, pet);
    cout << pet << endl;
    // player's inventory
    filein >> num;
    getline(filein, c);

    for(int i = 0; i < num; i++){
        getline(filein, itemName);
        if(itemName == "no weapon"){
            Item* n = new Item("no weapon", 0, 0, 0, 0);
            player->addItem(n);
            continue;
        }
        found = false;
        for(int rooms_num = 0; rooms_num < 9; i++){

            vector<Object*> objects = rooms[rooms_num]->getObjects();
            for(unsigned object_num = 0; object_num < objects.size(); object_num++){
                if(objects[object_num]->getTag() == "npc"){
                    NPC* npc = dynamic_cast<NPC*> (objects[object_num]);
                    vector<Item*> items = npc->getCommodity();

                    for(unsigned items_num = items.size(); items_num > 0; items_num--){
                        if(items[items_num-1]->getName() == itemName){
                            player->addItem(items[items_num-1]);

                            if(itemName == weapon){
                                player->setWeapon(items[items_num-1]);
                            }else if(itemName == pet){
                                player->setPet(items[items_num-1]);
                            }

                            npc->removeCommodity(items_num-1);
                            //cout << items[items_num-1] << endl;
                            rooms[rooms_num]->replaceObject(object_num, (Object*)npc);
                            found = true;
                            break;
                        }
                    }

                }

            }
            if(found) break;
        }

    }

    filein >> num;
    player->setCurrentRoom(rooms[num]);
    filein >> num;
    player->setPreviousRoom(rooms[num]);
}

void Record::loadRooms(vector<Room*>& rooms, ifstream& filein){
    int num;

    for(int i = 0; i < 9; i++){
        //cout << "a" << endl;
        filein >> num;
        vector<Object*> objects = rooms[i]->getObjects();
        if(num == 0){
            for(int object_num = objects.size(); object_num > 0; object_num--){
                rooms[i]->popObject(objects[object_num-1]);
            }
        }else if(num == 2){
            continue;
        }else if(num == 1){
            if(rooms[i]->getObjects().size() > num){
                rooms[i]->popObject(objects[0]);
            }
        }
    }
    if(rooms[5]->getObjects().size() < 2){
        if(rooms[1]->getObjects().size() != 0)
            rooms[1]->popObject(rooms[1]->getObjects()[0]);
    }

}

void Record::loadFromFile(Player* player, vector<Room*>& rooms){
    ifstream instream;
    instream.open("Dungeon.txt");

    this->loadPlayer(player, rooms, instream);
    this->loadRooms(rooms, instream);

    instream.close();
}
