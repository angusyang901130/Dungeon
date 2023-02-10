#include "Dungeon.h"

Dungeon::Dungeon(){
    // empty for now
}

void Dungeon::createPlayer(){
    string name;
    cout << "Please Enter your player name: " ;
    cin >> name;
    cin.sync();

    this->player = new Player(name, 100, 20, 30, 10);
    cout << "Welcome " << this->player->getName() << endl;
    this->player->setCurrentRoom(rooms[0]);
    this->player->setPreviousRoom(rooms[0]);

    // default weapon
    Item* item = new Item("no weapon", 0, 0, 0, 0);
    item->setTag("default");
    this->player->setWeapon(item);
    this->player->addItem(item);
}

void Dungeon::createMap(){
    // create the empty room for the vector
    for(int i = 0; i < 9; i++){

        Room* room = new Room();
        this->rooms.push_back(room);
        this->rooms[i]->setIndex(i);

        if(i == 8){
            this->rooms[i]->setIsExit(true);
        }else this->rooms[i]->setIsExit(false);
    }

    // the followings are the setting of the map

    // room 0 with 1 room around
    rooms[0]->setDownRoom(rooms[2]);

    // room 1 with 1 room around
    rooms[1]->setRightRoom(rooms[2]);

    // room 2 with 4 rooms around
    rooms[2]->setUpRoom(rooms[0]);
    rooms[2]->setDownRoom(rooms[4]);
    rooms[2]->setLeftRoom(rooms[1]);
    rooms[2]->setRightRoom(rooms[3]);

    // room 3 with 2 rooms around
    rooms[3]->setDownRoom(rooms[5]);
    rooms[3]->setLeftRoom(rooms[2]);

    // room 4 with 3 rooms around
    rooms[4]->setUpRoom(rooms[2]);
    rooms[4]->setDownRoom(rooms[7]);
    rooms[4]->setRightRoom(rooms[5]);

    // room 5 with 3 rooms around
    rooms[5]->setRightRoom(rooms[6]);

    // room 6 with 2 rooms around
    rooms[6]->setLeftRoom(rooms[5]);
    rooms[6]->setDownRoom(rooms[8]);

    // room 7 with 1 room around
    rooms[7]->setUpRoom(rooms[4]);

    // room 8 with 1 room around
    rooms[8]->setUpRoom(rooms[6]);
}

void Dungeon::createRoom(){
    // the followings are the character of the room

    // room 0
    NPC *host = new NPC();
    host->setScript("Welcome to the game\nI have something for you");
    host->setName("Host");
    host->setTag("npc");

    Item* pistol = new Item("Pistol", 0, 10, 0, 0);
    pistol->setTag("weapon");
    host->setCommodity(pistol);

    Item* cure = new Item("The Cure", 30, 0, 0, 0);
    cure->setTag("potion");
    host->setCommodity(cure);

    this->rooms[0]->addObject((Object*)host);


    // room 1
    vector<Item*> goods;

    Item* sword = new Item("Arthur's Sword", 0, 20, 10, 25);
    sword->setTag("weapon");
    goods.push_back(sword);

    Item* suit = new Item("Iron Suit", 0, 10, 15, 20);
    suit->setTag("weapon");
    goods.push_back(suit);

    Item* bow = new Item("Katniss's Bow", 0, 30, 0, 30);
    bow->setTag("weapon");
    goods.push_back(bow);

    Item* life1 = new Item("Life I", 60, 0, 0, 25);
    life1->setTag("potion");
    goods.push_back(life1);

    NPC* vendor = new NPC("Notorious Vendor", "Gee Gee\nWelcome to my store\nIs there anything you want?", goods);
    vendor->setTag("npc");

    this->rooms[1]->addObject((Object*)vendor);


    // room 2
    Monster* zombie = new Monster("Speedy Zombie", 50, 20, 20, 15);  // give 10 dollars when defeat the monster
    this->rooms[2]->addObject((Object*)zombie);


    // room 3
    Monster* samurai = new Monster("Three-Sword Samurai", 100, 30, 45, 25);  // give 30 dollars when defeat the monster
    this->rooms[3]->addObject((Object*)samurai);


    // room 4
    NPC* farmer = new NPC();
    farmer->setName("The Great Farmer");
    farmer->setTag("npc");
    farmer->setScript("Welcome to my farm, do you want to get some pet? It's free for you!");

    Item* bull = new Item("Adorable Bull", 0, 20, 20, 0);
    bull->setTag("pet");
    farmer->setCommodity(bull);

    this->rooms[4]->addObject((Object*)farmer);


    // room 5
    NPC* giver = new NPC();
    giver->setName("The Giver");
    giver->setTag("npc");
    giver->setScript("I always treat my customers with my real heart\nBut you have to treat me with your real heart, too");

    Item* shield = new Item("Captain's Shield", 0, 50, 50, 0);
    shield->setTag("weapon");
    giver->setCommodity(shield);

    this->rooms[5]->addObject((Object*)giver);


    // room 6
    Monster* dragon = new Monster("Fire Dragon", 200, 65, 65, 50);  // give 50 dollars when defeat the monster

    NPC* wizard = new NPC();
    wizard->setName("Mysterious Wizard");
    wizard->setTag("npc");
    wizard->setScript("Do you want to be undefeated?");

    Item* life2 = new Item("Life II", 100, 0, 0, 40);
    life2->setTag("potion");
    wizard->setCommodity(life2);

    Item* survivor = new Item("Survivor", 80, 10, 10, 40);
    survivor->setTag("potion");
    wizard->setCommodity(survivor);

    this->rooms[5]->addObject((Object*)dragon);
    this->rooms[6]->addObject((Object*)wizard);


    // room 7
    NPC* warrior = new NPC();
    warrior->setName("Injured Warrior");
    warrior->setTag("npc");
    warrior->setScript("The crazy monster in the room just block my way back home\nCan you help me to defeat the monster?");

    Monster* robot = new Monster("Razor Robot", 150, 40, 50, 40);

    this->rooms[7]->addObject((Object*)warrior);
    this->rooms[7]->addObject((Object*)robot);  // set health to 150


    // room 8
    Monster* godrilla = new Monster("Godrilla", 300, 75, 75, 0);
    this->rooms[8]->addObject((Object*)godrilla);

}

bool Dungeon::listAction(vector<Object*> objects){
    string ans;

    // show the list what the player can do at the moment
    if(objects.size() == 0){
        // no more object
        cout << "What do you want to do now?" << endl;
        cout << "<a> Move to another room" << endl;     // move
        cout << "<b> Show my status now" << endl;       // player->triggerEvent
        cout << "<c> Leave game" << endl;               // record

        while(getline(cin, ans)){
            cin.sync();

            if(ans != "a" && ans != "b" && ans != "c"){
                cout << "Invalid Input" << endl;
                cout << "What do you want to do you now? " << endl;
                cout << "<a> Move to another room" << endl;
                cout << "<b> Show my status now" << endl;
                cout << "<c> Leave game" << endl;
            }else break;

        }

        if(ans == "a"){
            this->handleMovement();
            return false;
        }else if(ans == "b"){
            this->handleEvent((Object*)this->player);
            return false;
        }else if(ans == "c"){
            return true;
        }

    }else if(objects[0]->getTag() == "monster" || objects.size() == 2){
        // if there is monster, then you must defeat it to advance
        cout << "What do you want to do now?" << endl;
        cout << "<a> Meet the hosts of the room" << endl;           // handleEvent
        cout << "<b> Show my status now" << endl;                   // player->triggerEvent
        cout << "<c> Leave game" << endl;                           // record

        while(getline(cin, ans)){
            cin.sync();

            if(ans != "a" && ans != "b" && ans != "c"){
                cout << "Invalid Input" << endl;
                cout << "What do you want to do you now? " << endl;
                cout << "<a> Meet the hosts of the room" << endl;
                cout << "<b> Show my status now" << endl;
                cout << "<c> Leave game" << endl;
            }else break;

        }

        if(ans == "a"){
            this->chooseAction(this->rooms[this->player->getCurrentRoom()->getIndex()]->getObjects());
            return false;
        }else if(ans == "b"){
            this->handleEvent((Object*)this->player);
            return false;
        }else if(ans == "c"){
            return true;
        }

    }else{
        // normal type
        cout << "What do you want to do now?" << endl;
        cout << "<a> Move to another room" << endl;             // move
        cout << "<b> Meet the hosts of the room" << endl;       // handleEvent
        cout << "<c> Show my status now" << endl;               // player->triggerEvent
        cout << "<d> Leave game" << endl;                       // record

        while(getline(cin, ans)){
            cin.sync();

            if(ans != "a" && ans != "b" && ans != "c" && ans != "d"){
                cout << "Invalid Input" << endl;
                cout << "What do you want to do you now? " << endl;
                cout << "<a> Move to another room" << endl;
                cout << "<b> Meet the hosts in the room" << endl;
                cout << "<c> Show my status now" << endl;
                cout << "<d> Leave game" << endl;
            }else break;

        }

        if(ans == "a"){
            this->handleMovement();   // move
            return false;
        }else if(ans == "b"){
            this->chooseAction(this->rooms[this->player->getCurrentRoom()->getIndex()]->getObjects());   // interact with the objects
            return false;
        }else if(ans == "c"){
            this->handleEvent((Object*)this->player);   // player ->triggerEvent
            return false;
        }else if(ans == "d"){
            return true;   // record
        }

    }

}

void Dungeon::handleMovement(){
    string move;
    char m;
    int count;
    int dir = 0;

    // show the direction of the current Room
    cout << "Please enter the direction you want to go:" << endl;
    count = 0;
    for(int i = 0; i < 4; i++){

        if(i == 0){

            Room* UpRoom = this->player->getCurrentRoom()->getUpRoom();
            if(UpRoom != NULL){
                cout << "<" << (char)('a'+count) << "> " << "Up";

                vector<Object*> UpObjects = UpRoom->getObjects();
                for(unsigned ob = 0; ob < UpObjects.size(); ob++){
                    if(UpObjects[ob]->getTag() == "monster"){
                        cout << " (monster place)";
                    }
                }
                cout << endl;
                count++;

            }

        }else if(i == 1){

            Room* DownRoom = this->player->getCurrentRoom()->getDownRoom();
            if(this->player->getCurrentRoom()->getDownRoom() != NULL){
                cout << "<" << (char)('a'+count) << "> " << "Down";
                vector<Object*> DownObjects = DownRoom->getObjects();
                for(unsigned ob = 0; ob < DownObjects.size(); ob++){
                    if(DownObjects[ob]->getTag() == "monster"){
                        cout << " (monster place)";
                    }
                }
                cout << endl;
                count++;
            }

        }else if(i == 2){

            Room* LeftRoom = this->player->getCurrentRoom()->getLeftRoom();
            if(this->player->getCurrentRoom()->getLeftRoom() != NULL){
                cout << "<" << (char)('a'+count) << "> " << "Left";

                vector<Object*> LeftObjects = LeftRoom->getObjects();
                for(unsigned ob = 0; ob < LeftObjects.size(); ob++){
                    if(LeftObjects[ob]->getTag() == "monster"){
                        cout << " (monster place)";
                        break;
                    }
                }
                cout << endl;
                count++;
            }

        }else if(i == 3){

            Room* RightRoom = this->player->getCurrentRoom()->getRightRoom();
            if(this->player->getCurrentRoom()->getRightRoom() != NULL){
                cout << "<" << (char)('a'+count) << "> " << "Right";

                vector<Object*> RightObjects = RightRoom->getObjects();
                for(unsigned ob = 0; ob < RightObjects.size(); ob++){
                    if(RightObjects[ob]->getTag() == "monster"){
                        cout << " (monster place)";
                    }
                }
                cout << endl;
                count++;
            }

        }
    }

    // input the direction the player wants to go
    while(cin >> move){
        cin.sync();

        if(move != "a" && move != "b" && move != "c" && move != "d"){

            cout << "Invalid Input" << endl;
            cout << "Please enter the direction you want to go:" << endl;
            count = 0;
            for(int i = 0; i < 4; i++){

                if(i == 0){

                    Room* UpRoom = this->player->getCurrentRoom()->getUpRoom();
                    if(UpRoom != NULL){
                        cout << "<" << (char)('a'+count) << "> " << "Up";

                        vector<Object*> UpObjects = UpRoom->getObjects();
                        for(unsigned ob = 0; ob < UpObjects.size(); ob++){
                            if(UpObjects[ob]->getTag() == "monster"){
                                cout << " (monster place)";
                            }
                        }
                        cout << endl;
                        count++;
                    }

                }else if(i == 1){

                    Room* DownRoom = this->player->getCurrentRoom()->getDownRoom();
                    if(this->player->getCurrentRoom()->getDownRoom() != NULL){
                        cout << "<" << (char)('a'+count) << "> " << "Down";

                        vector<Object*> DownObjects = DownRoom->getObjects();
                        for(unsigned ob = 0; ob < DownObjects.size(); ob++){
                            if(DownObjects[ob]->getTag() == "monster"){
                                cout << " (monster place)";
                            }
                        }
                        cout << endl;
                        count++;

                    }

                }else if(i == 2){

                    Room* LeftRoom = this->player->getCurrentRoom()->getLeftRoom();
                    if(this->player->getCurrentRoom()->getLeftRoom() != NULL){
                        cout << "<" << (char)('a'+count) << "> " << "Left";

                        vector<Object*> LeftObjects = LeftRoom->getObjects();
                        for(unsigned ob = 0; ob < LeftObjects.size(); ob++){
                            if(LeftObjects[ob]->getTag() == "monster"){
                                cout << " (monster place)";
                            }
                        }
                        cout << endl;
                        count++;
                    }

                }else if(i == 3){

                    Room* RightRoom = this->player->getCurrentRoom()->getRightRoom();

                    if(this->player->getCurrentRoom()->getRightRoom() != NULL){
                        cout << "<" << (char)('a'+count) << "> " << "Right";

                        vector<Object*> RightObjects = RightRoom->getObjects();
                        for(unsigned ob = 0; ob < RightObjects.size(); ob++){
                            if(RightObjects[ob]->getTag() == "monster"){
                                cout << " (monster place)";
                            }
                        }
                        cout << endl;
                        count++;

                    }

                }

            }

        }else break;
    }

    // input move assign to m
    m = move[0];

    // transfer to the room
    for(int i = 0; i < 4; i++){

        if(i == 0){
            if(this->player->getCurrentRoom()->getUpRoom() != NULL){

                if(dir == m - 'a' ){
                    this->player->changeRoom(this->player->getCurrentRoom()->getUpRoom());
                    cout <<  "You are moving to the upper Room" << endl;
                    break;
                }else dir++;

            }
        }else if(i == 1){
            if(this->player->getCurrentRoom()->getDownRoom() != NULL){

                if(dir == m - 'a' ){
                    this->player->changeRoom(this->player->getCurrentRoom()->getDownRoom());
                    cout <<  "You are moving to the downer Room" << endl;
                    break;
                }else dir++;

            }
        }else if(i == 2){
            if(this->player->getCurrentRoom()->getLeftRoom() != NULL){

                if(dir == m - 'a' ){
                    this->player->changeRoom(this->player->getCurrentRoom()->getLeftRoom());
                    cout <<  "You are moving to the left Room" << endl;
                    break;
                }else dir++;

            }
        }else if(i == 3){
            if(this->player->getCurrentRoom()->getRightRoom() != NULL){

                if(dir == m - 'a' ){
                    this->player->changeRoom(this->player->getCurrentRoom()->getRightRoom());
                    cout <<  "You are moving to the right Room" << endl;
                    break;
                }else dir++;

            }
        }

    }

}


void Dungeon::chooseAction(vector<Object*> objects){
    string ans;

    if(objects.size() == 0){
        cout << "Everyone in the room is gone" << endl;
        cout << "This is an empty room?\n" << "Do you want to move to another room?" << endl;
        return;
    }else{
        cout << "It seems like there is somebody here\n" << endl;
    }

    if(objects.size() == 2){
        cout << objects[0]->getName() << " wants to talk to you" << endl;
        this->handleEvent(objects[0]);
        cout << endl;
        cout << "You just discover The Monster " << "<" << objects[1]->getName() << ">" << endl;
        this->handleEvent(objects[1]);
        cout << endl;
    }else if(objects.size() == 1){
        if(objects[0]->getTag() == "monster"){
            cout << "You just discover The Monster " << "<" << objects[0]->getName() << ">" << endl;
            this->handleEvent(objects[0]);
        }else this->handleEvent(objects[0]);    // meet the npc
    }

}

void Dungeon::handleEvent(Object* object){

    // decide the triggerEvent
    if(object->getTag() == "monster"){

        Monster* monster = dynamic_cast<Monster*> (object);

        if(monster->triggerEvent((Object*)this->player)){
            this->player->getCurrentRoom()->popObject(object);
            if(monster->getName() == "Fire Dragon"){
                cout << "Oops, the dragon just broke the way back, there is only one way left" << endl;
            }
        }

    }else if(object->getTag() == "npc"){

        NPC* npc = dynamic_cast<NPC*> (object);

        if(npc->triggerEvent((Object*)this->player)){
            this->player->getCurrentRoom()->popObject(object);
        }

    }else if(object->getTag() == "player"){

        if(this->player->triggerEvent((Object*)this->player)){
            cout << endl;
        }

    }
}


bool Dungeon::checkGameLogic(){
    if(this->player->getCurrentRoom()->getIsExit() && this->player->getCurrentRoom()->getObjects().size() == 0){
        cout << "You just beat the Boss of the Dungeon!" << endl;
        cout << "You get the Treasure!" << endl;
        cout << "You now have one million dollars" << endl;
        cout << "Game Finish" << endl;
        return true;
    }else return false;
}


void Dungeon::startGame(){
    string ans;
    fstream file;

    file.open("Dungeon.txt");
    if(file.fail()){
        this->createMap();
        this->createRoom();
        this->createPlayer();
    }else{
        this->createMap();
        this->createRoom();
        cout << "Continue playing? (y/n) ";

        while(cin >> ans){
            if(ans != "y" && ans != "n"){
                cout << "Invalid input" << endl;
                cout << "Continue playing? (y/n) ";
            }else break;
        }

        if(ans == "y"){
            Record record;
            this->player = new Player();
            record.loadFromFile(this->player, this->rooms);
        }else{
            this->createPlayer();
        }

    }

}


void Dungeon::runDungeon(){
    Record record;
    this->startGame();
    while(!this->checkGameLogic()){
        cin.sync();
        cout << endl;
        cout << "You are now in Room " << this->player->getCurrentRoom()->getIndex() << endl;
        cout << endl;

        if(this->listAction(this->player->getCurrentRoom()->getObjects())){
            cout << "Save to File" << endl;
            break;
        }

    }
    if(!this->checkGameLogic()){
        record.saveToFile(this->player, this->rooms);
    }
}
