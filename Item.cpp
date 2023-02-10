#include "Item.h"

Item::Item(){
    // empty for now
}

Item::Item(string name, int health, int attack, int defense, int price):Object(name, "item"){
    this->health = health;
    this->attack = attack;
    this->defense = defense;
    this->price = price;
}

void Item::setHealth(int Health){
    this->health = Health;
}

void Item::setAttack(int Attack){
    this->attack = attack;
}

void Item::setDefense(int Defense){
    this->defense = Defense;
}

int Item::getHealth(){
    return this->health;
}

int Item::getAttack(){
    return this->attack;
}

int Item::getDefense(){
    return this->defense;
}

void Item::setPrice(int price){
    this->price = price;
}

int Item::getPrice(){
    return this->price;
}

bool Item::triggerEvent(Object* object){
    vector<int> item;
    int count = 0;
    string ans;

    Player* player = dynamic_cast<Player*> (object);
    vector<Item*> inventory(player->getInventory());
    cout << "Which one do you want to use? " << endl;

    // deal with the weapon the player want to use
    for(unsigned i = 0; i < inventory.size(); i++){

        if(inventory[i]->getTag() == "weapon" || inventory[i]->getTag() == "default"){

            if(inventory[i]->getName() != player->getWeapon()->getName()){
                cout << "<" << (char)('a'+count) << "> " << inventory[i]->getName() << " A: " << inventory[i]->getAttack() << " D: " << inventory[i]->getDefense() << endl;
                item.push_back(i);
                count++;
            }

        }

    }

    if(count == 0 && this->getAttack() == 0){   // meaning no weapon
        cout << "Oops, you got to fight bare-handed" << endl;
        return true;
    }else if(count == 0){   // meaning no additional weapon
        cout << "Oops, you only got a weapon" << endl;
        return false;
    }else cout << "<" << (char)('a'+count) << ">" << "use the same weapon" << endl;  // use the same one

    // input the weapon the player want to use
    while(getline(cin, ans)){
        cin.sync();
        if(count == 1){
            if(ans != "a" && ans != "b"){
                cout << "Invalid Input\n" << "Which one do you want to use?" << endl;
            }else break;
        }else if(count == 2){
            if(ans != "a" && ans != "b" && ans != "c"){
                cout << "Invalid Input\n" << "Which one do you want to use?" << endl;
            }else break;
        }else if(count == 3){
            if(ans != "a" && ans != "b" && ans != "c" && ans != "d"){
                cout << "Invalid Input\n" << "Which one do you want to use?" << endl;
            }else break;
        }else if(count == 4){
            if(ans != "a" && ans != "b" && ans != "c" && ans != "d" && ans != "e"){
                cout << "Invalid Input\n" << "Which one do you want to use?" << endl;
            }else break;
        }
    }

    // select the weapon
    if(ans == "a"){
        if(count == 0){
            return false;
        }
        player->increaseStates(0, -player->getWeapon()->getAttack(), -player->getWeapon()->getDefense());
        player->setWeapon(player->getItem(item[0]));
        return true;
    }else if(ans == "b"){
        if(count == 1){
            return false;
        }
        player->increaseStates(0, -player->getWeapon()->getAttack(), -player->getWeapon()->getDefense());
        player->setWeapon(player->getItem(item[1]));
        return true;
    }else if(ans == "c"){
        if(count == 2){
            return false;
        }
        player->increaseStates(0, -player->getWeapon()->getAttack(), -player->getWeapon()->getDefense());
        player->setWeapon(player->getItem(item[2]));
        return true;
    }else if(ans == "d"){
        if(count == 3){
            return false;
        }
        player->increaseStates(0, -player->getWeapon()->getAttack(), -player->getWeapon()->getDefense());
        player->setWeapon(player->getItem(item[3]));
        return true;
    }else if(ans == "e"){
        return false;
    }
}
