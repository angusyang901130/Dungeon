#include "NPC.h"

NPC::NPC(){
    // empty for purpose
}

NPC::NPC(string name, string script, vector<Item*> commodity):GameCharacter(name, "npc", 0, 0, 0){
    this->script = script;
    this->commodity = commodity;
}

void NPC::listCommodity(){
    for(unsigned i = 0; i < this->commodity.size(); i++){
        cout << "<" << (char)('a'+i) << "> " << this->commodity[i]->getName() << endl;
        cout << " Type:" << this->commodity[i]->getTag() << endl;
        cout << " H:" << this->commodity[i]->getHealth() << endl;
        cout << " A:" << this->commodity[i]->getAttack() << endl;
        cout << " D:" << this->commodity[i]->getDefense() << endl;
        cout << "Price:" << this->commodity[i]->getPrice() << endl;
        cout << endl;
    }
}

void NPC::setScript(string script){
    this->script = script;
}

string NPC::getScript(){
    return this->script;
}

void NPC::setCommodities(vector<Item*> commodity){
    this->commodity = commodity;
}

vector<Item*> NPC::getCommodity(){
    return this->commodity;
}

bool NPC::buyItem(Player* player,Item* item){
    if(player->getMoney() >= item->getPrice()){
        player->setMoney(player->getMoney() - item->getPrice());
        player->addItem(item);
        cout << endl;
        cout << "Now you have received the item" << endl;
        cout << "Now the you got " << player->getMoney() << " dollars remain" << endl;
        return true;
    }else{
        cout << "Oops, you don't have enough money" << endl;
        cout << "Goodbye, go earn some money and come back" << endl;
        return false;
    }
}

void NPC::setCommodity(Item* item){
    this->commodity.push_back(item);
}

void NPC::removeCommodity(int num){
    this->commodity.erase(this->commodity.begin()+num);
}

bool NPC::triggerEvent(Object* object){
    string ans;
    Player* player = dynamic_cast<Player*> (object);
    vector<Item*> inventory(player->getInventory());

    cout << "You are going to meet " << this->getName() << endl;
    cout << endl;
    cout << "Hello, I am " << this->getName() << endl;

    // 1. show the script
    cout << this->getScript() << endl;

    // only for the warrior
    if(this->getCommodity().size() == 0){
        cout << "I will give you some money to help you " << endl;
        player->setMoney(player->getMoney()+20);
        return true;
    }

    cout << "Do you want to get something from me? (y/n) ";

    // 2. ask if the player want something
    while(getline(cin, ans)){
        cin.sync();

        if(ans != "y" && ans != "n"){
            cout << "Invalid Input\n" << "Do you want to get something from me? (y/n) ";
        }else break;

    }

    if(ans == "y"){
        cout << endl;
        cout << "You got " << player->getMoney() << " dollars " << endl;
        cout << endl;
        cout << "Here are the things I have:" << endl;


        // 3-1 there is a trader
        if(this->getName() == "The Giver"){

            cout << this->commodity[0]->getName() << endl;
            cout << "A: " << this->commodity[0]->getAttack() << endl;
            cout << "D: " << this->commodity[0]->getDefense() << endl;

            cout << "I only give my masterpiece to the braves, you must also defeat 3 monsters to get it" << endl;
            cout << endl;
            if(player->getDefeatNum() < 3){
                cout << "You defeat " << player->getDefeatNum() << "monster(s)" << endl;
                cout << "Oops, seems like you haven't defeat 3 monsters" << endl;
                player->changeRoom(player->getPreviousRoom());
                cout << "Sending you back to the previous Room" << endl;
                return false;
            }

            cout << "Alright, You defeated 3 monsters, but you have to give me all of your money and weapon to me for my masterpiece" << endl;
            cout << "Otherwise, I will not let you in" << endl;

            cout << "Do you want to continue the trade? (y/n) ";

            while(getline(cin, ans)){
                cin.sync();
                if(ans != "y" && ans != "n"){
                    cout << "Invalid Input\n" << "Do you want to continue the trade? (y/n) ";
                }else break;
            }

            if(ans == "y"){
                cout << "You will be glad with my masterpiece" << endl;
                player->setMoney(0);

                for(unsigned i = inventory.size(); i > 0; i--){
                    if(inventory[i-1]->getTag() == "weapon"){
                        player->removeItem(i-1);
                    }
                }

                player->addItem(this->commodity[0]);
                this->removeCommodity(0);

            }else{
                cout << "Well, I can't let you in" << endl;
                player->changeRoom(player->getPreviousRoom());
                cout << "Sending you back to the previous Room" << endl;
                return false;
            }

        }

        // 3-2 there is a seller
        else{

            this->listCommodity();
            cout << "Do you want to get something? (y/n) ";

            // input
            while(getline(cin, ans)){
                if(ans != "y" && ans != "n"){
                    cout << "Invalid Input\n" << "Do you want to get something? (y/n) ";
                }else break;
            }

            if(ans == "y"){

                cout << "Which one do you want? ";
                // ask the player to choose
                while(getline(cin, ans)){
                    cin.sync();
                    if(this->commodity.size() == 1){
                        if(ans != "a"){
                            cout << "Invalid Input\n" << "Which one do you want to buy? ";
                        }else break;
                    }else if(this->commodity.size() == 2){
                        if(ans != "a" && ans != "b"){
                            cout << "Invalid Input\n" << "Which one do you want to buy? ";
                        }else break;
                    }else if(this->commodity.size() == 3){
                        if(ans != "a" && ans != "b" && ans != "c"){
                            cout << "Invalid Input\n" << "Which one do you want to buy? ";
                        }else break;
                    }else if(this->commodity.size() == 4){
                        if(ans != "a" && ans != "b" && ans != "c" && ans != "d"){
                            cout << "Invalid Input\n" << "Which one do you want to buy? ";
                        }else break;
                    }
                }

                // check if the player could buy
                if(ans == "a"){
                    if(this->buyItem(player, this->commodity[0])){

                        // only for the farmer
                        if(this->commodity[0]->getTag() == "pet"){
                            player->setPet(this->commodity[0]);
                            player->increaseStates(0, player->getPet()->getAttack(), player->getPet()->getDefense());
                        }

                        // npc no longer own the thing
                        this->removeCommodity(0);
                        cout << "Thank you" << endl;
                    }
                }else if(ans == "b"){
                    if(this->buyItem(player, this->commodity[1])){
                        // npc no longer own the thing
                        this->removeCommodity(1);
                        cout << "Thank you" << endl;
                    }
                }else if(ans == "c"){
                    if(this->buyItem(player, this->commodity[2])){
                        // npc no longer own the thing
                        this->removeCommodity(2);
                        cout << "Thank you" << endl;
                    }
                }else if(ans == "d"){
                    if(this->buyItem(player, this->commodity[3])){
                        // npc no longer own the thing
                        this->removeCommodity(3);
                        cout << "Thank you" << endl;
                    }
                }
            }else{
                cout << "Well, see you next time" << endl;
            }

        }
    }else{
        cout << "Well, see you next time" << endl;
    }

    if(this->commodity.size() == 0){
        return true;
    }else return false;

}
