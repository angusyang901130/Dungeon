#include "Monster.h"

Monster::Monster(){
    // empty for purpose
}

Monster::Monster(string name, int health, int attack, int defense, int price):GameCharacter(name, "monster", health, attack, defense){
    this->price = price;
}

void Monster::setPrice(int price){
    this->price = price;
}

int Monster::getPrice(){
    return this->price;
}

bool Monster::triggerEvent(Object* object){
    string ans;
    int random;
    Player* player = dynamic_cast<Player*> (object);
    vector<Item*> inventory(player->getInventory());

    cout << player->getName() << " V.S " << this->getName() << endl;
    cout << endl;
    cout << "choose your weapon" << endl;
    cout << endl;

    if(player->getWeapon()->triggerEvent((Object*)player)){
        player->increaseStates(0, player->getWeapon()->getAttack(), player->getWeapon()->getDefense());
    }

    cout << "You are using " << player->getWeapon()->getName() << endl;

    // use random number for the monster to fight
    srand( time(NULL) );

    cout << "Start Fighting" << endl;
    while(!player->checkIsDead() && !this->checkIsDead()){

        if(player->triggerEvent((Object*)player)){
            cout << "The monster's status: " << endl;
        }

        cout << "A: " << this->getAttack() << " D: " << this->getDefense() << " H: " << this->getCurrentHealth()
             << "/" << this->getMaxHealth() << endl;
        cout << endl;

        cout << "You are using ";
        cout << player->getWeapon()->getName() << " A: " << player->getWeapon()->getAttack() << " D: "
             << player->getWeapon()->getDefense() << endl;  // show the weapon the player has
        cout << endl;
        cout << "Change Your weapon? (y/n) " ;

        // input the answer
        while(getline(cin, ans)){
            cin.sync();
            cout << endl;

            if(ans != "y" && ans != "n"){
                cout << "Invalid Input" << endl;
                cout << "Change Your weapon? (y/n) " << endl;
            }else break;

        }

        // y then change ,  n then stay the same
        if(ans == "y"){

            if(player->getWeapon()->triggerEvent((Object*)player)){                     // have to new a weapon
                player->increaseStates(0, player->getWeapon()->getAttack(), player->getWeapon()->getDefense());
            }

        }else if(ans == "n"){

            cout << "Alright, you are courageous" << endl;

        }

        // now choose to attack or defense
        cout << "Choose to Attack or Defense" << endl;
        cout << "<a> Attack\n" << "<b> Defense\n" << "<c> Retreat "<<endl;

        // input
        while(getline(cin, ans)){
            cin.sync();

            if(ans != "a" && ans != "b" && ans != "c"){
                cout << "Invalid input" << endl;
                cout << "Choose to Attack or Defense" << endl;
                cout << "<a> Attack\n" << "<b> Defense\n" << "<c> Retreat "<<endl;
            }else break;

        }

        if(ans == "c"){
            player->changeRoom(player->getPreviousRoom());
            cout << "You are being sent back to the previous Room" << endl;
            cout << endl;
            return false;
        }

        // the monster is randomly choosing attack or defense
        random = rand() % 100;

        if(random >= 50){
            cout << this->getName() << " chooses attack" << endl;
        }else cout << this->getName() << " chooses defense" << endl;

        // to compare the result of fight
        if(ans == "a"){
            cout << "You choose Attack" << endl;
            cout << endl;

            if(random < 50){

                if(player->getAttack() > this->getDefense()){
                    cout << "Your attack works! Keep going" << endl;
                    // you beat his defense
                    this->takeDamage(player->getAttack() - this->getDefense());
                }else cout << "Your attack doesn't work" << endl;

            }else if(random >= 50){

                cout << "Let's see who is better" << endl;
                // both get harm
                player->takeDamage(this->getAttack());
                this->takeDamage(player->getAttack());

            }

        }else if(ans == "b"){
            cout << "You choose defense" << endl;

            if(random < 50){
                // both defense
                cout << "Both safe!" << endl;
            }else if(random >= 50){

                if(player->getDefense() >= this->getAttack()){
                    // you are safe from his attack
                    cout << "Alright, you are tough" << endl;
                }else{
                    // you are harm
                    cout << "I can harm you!" << endl;
                    player->takeDamage(this->getAttack() - player->getDefense());
                }

            }

        }

    }

    // check if the fight is over
    if(player->checkIsDead() && !this->checkIsDead()){
        cout << "Too bad, you just lost" << endl;
        cout << "Sending you back to previous Room" << endl;
        cout << endl;
        // player dies then send back to the previous room
        player->changeRoom(player->getPreviousRoom());

        // see if he got potion
        if(player->getInventory().size() == 0){
            player->setCurrentHealth(30);
        }else{

            for(unsigned i = 0; i < inventory.size(); i++){
                if(inventory[i]->getTag() == "potion"){
                    player->increaseStates(inventory[i]->getHealth(), inventory[i]->getAttack(),  inventory[i]->getDefense());
                }
            }

            // if no potion
            if(player->getCurrentHealth() == 0){
                player->setCurrentHealth(30);
            }else cout << "Your potions cure you" << endl;
        }

        if(player->triggerEvent((Object*)player)){
            cout << "You are alive now" << endl;
        }

        return false;
    }

    // to check if win the monster
    if(this->checkIsDead()){
        cout << "You win ! >o<" << endl;

        // get price from the monster
        player->setMoney(player->getMoney()+this->getPrice());
        player->setDefeatNum(player->getDefeatNum()+1);
        cout << "You got " << this->getPrice() << " dollars" << endl;

        // set the health
        player->setMaxHealth(player->getMaxHealth()+25);
        player->setCurrentHealth(player->getMaxHealth());

        return true;
    }

}
